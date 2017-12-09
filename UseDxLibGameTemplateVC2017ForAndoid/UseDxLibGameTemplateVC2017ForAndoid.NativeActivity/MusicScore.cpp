#include "MusicScore.h"

void MusicScore::loadMusicScore(int difficulty)
{
	this->filePath = musicInfo.getFilePath() + static_cast<char>('0' + difficulty) + ".tsv";
	std::ifstream ifs(this->filePath);
	std::string line;
	bool isHumen = false;
	float bpm = 1;
	double nowTime = 0;
	double lastPeriod = 1;
	double nowPeriod = 1;
	int divPeriod = 4; //小節分割数
	int numBeatDiv = 4; // div分のnumDiv拍子
	int beatDiv = 4;
	std::map<int, int> useId; //id, uid(配列番号) LN以外
	std::map<int, int> useLnId; //line, uid LN専用
	int uid = 0;

	judgeLine.setNumLine(5);

	while (std::getline(ifs, line)) {
		//コメント行
		if (line.size() >= 2) {
			if (line[0] == '/' && line[1] == '/') continue;
		}

		//情報行
		//曲の時間は加算しない
		if (!line.empty() && line.front() == '#') {
			line = line.substr(1);
			std::stringstream ss(line);

			//引数たちを取得
			std::string tmp;
			std::vector<std::string> args;
			while (std::getline(ss, tmp, ' ')) {
				args.push_back(tmp);
			}

			if (args[0] == "BPM") {
				bpm = std::atof(args[1].c_str());
				//ピリオド経過数を更新
				nowTime += calcElapsedTime(lastPeriod, nowPeriod, bpm, numBeatDiv, beatDiv);
			}
			else if (args[0] == "StartTime") {
				startTime = std::atoi(args[1].c_str());
				nowTime = startTime;
			}
			else if (args[0] == "Humen") isHumen = true;
			else if (args[0] == "Key") {
				judgeLine.setNumLine(std::atoi(args[1].c_str()));
			}
			else if (args[0] == "Beat") {
				numBeatDiv = std::atoi(args[1].c_str());
				beatDiv = std::atoi(args[2].c_str());
			}
			else if (std::isdigit(args[0][0])) { //小節数スキップ
				lastPeriod = nowPeriod;
				nowPeriod = std::atof(args[0].c_str());
				divPeriod = std::atoi(args[1].c_str());
				nowTime += calcElapsedTime(lastPeriod, nowPeriod, bpm, numBeatDiv, beatDiv);
			}
			continue;
		}

		//譜面行
		std::stringstream ss(line);
		//譜面なしの行
		if(line.empty()) {}
		else { //譜面あり
			std::vector<std::string> noteInfo;
			std::string noteStr;
			int no = 0;
			while (std::getline(ss, noteStr, '\t')) {
				//ノート情報あり
				if (!noteStr.empty() && noteStr.front() != '-') {
					//引数を取得
					std::stringstream ss2(noteStr);
					std::vector<float> args;
					while (std::getline(ss2, noteStr)) {
						args.push_back(std::atof(noteStr.c_str()));
					}

					//ノート設定
					float appear = no;
					NoteType type;
					int id = 0;
					int endPoint = false; //LN等の終点
					type = static_cast<NoteType>(static_cast<int>(args[0]));
					if (args.size() >= 2) appear = args[1];
					if (args.size() >= 3) id = static_cast<int>(args[2]);
					if (args.size() >= 4) endPoint = true;


					//タイプ設定
					//FLICKはLN,SLIDE終点以外自動設定
					std::shared_ptr<Note> lastNote;
					//前のノートがあるならそれを利用するため保存
					if (useId.find(id) != useId.end() && type != NoteType::LN) {
						lastNote = notes[useId[id]];
					}
					else if (useLnId.find(no) != useLnId.end() && type == NoteType::LN) {
						lastNote = notes[useLnId[no]];
					}

					std::shared_ptr<Note> note;
					if (type == NoteType::NORMAL) {
						note = std::make_shared<NormalNote>();
					}
					else {
						std::shared_ptr<HaveNextNote> haveNextNote;
						switch (type) {
						case NoteType::LN: haveNextNote = std::make_shared<LongNote>(); break;
						case NoteType::SLIDE: 
						{
							std::shared_ptr<SlideNote> slideNote = std::make_shared<SlideNote>();
							if (lastNote) slideNote->setIsFirstNote(false);
							haveNextNote = slideNote;
						}
							break;
						case NoteType::FLICK_L:
						case NoteType::FLICK_R:
						{
							FlickDirection direction;
							if (type == NoteType::FLICK_L) direction = FlickDirection::FLICK_L;
							if (type == NoteType::FLICK_R) direction = FlickDirection::FLICK_R;

							std::shared_ptr<FlickNote> flickNote = std::make_shared<FlickNote>();
							//取り敢えず突っ込んどく
							flickNote->setDirection(direction);
							//前回のノートと照らし合わせてフリック方向を決定
							if (lastNote) {
								lastNote->setDirectionByNextNote(flickNote);
								flickNote->setDirectionByLastNote(lastNote);
							}
							haveNextNote = std::move(flickNote);
						}
						break;
						default: break;
						}

						//手前のノートに接続するノートを設定
						if (lastNote) {
							lastNote->setNextNote(haveNextNote);
						}
						note = std::move(haveNextNote);

						//次のノートを更新
						if (NoteType::LN < type && type <= NoteType::FLICK_R) {
							useId[id] = uid;
						}
						if (type == NoteType::LN) {
							useLnId[no] = uid;
						}

						//id開放 普通のLNは接続先が現れたら強制的に開放
						if (endPoint && (type != NoteType::LN)) {
							useId.erase(id);
						}
						else if ((endPoint || lastNote) && type == NoteType::LN) {
							useLnId.erase(no);
						}
					}

					//汎用設定して追加
					note->setting(no, appear, nowTime, uid, id);
					notes.push_back(std::move(note));

					//配列番号を進める
					uid++;
				}
				no++;
			}
		}

		//経過ピリオド数を更新
		lastPeriod = nowPeriod;
		nowPeriod += 1.0 / divPeriod / (numBeatDiv / beatDiv);
		nowTime += calcElapsedTime(lastPeriod, nowPeriod, bpm, numBeatDiv, beatDiv);
		continue;
	}

	//ノートを時間順にソート
	std::sort(notes.begin(), notes.end(), 
			  [](const std::shared_ptr<Note>& l, const std::shared_ptr<Note>& r) {
					return l->getJudgeTime() > r->getJudgeTime(); 
			  }
	);

	judgeLine.loadJudgeIcons();
	//音楽読み込み
	std::string musicFile = (musicInfo.getFilePath() + "bgm.ogg");
	bgm = LoadSoundMem(musicFile.c_str());
}

double MusicScore::calcElapsedTime(double lastPeriod, double nowPeriod, float bpm, int numBeatDiv, int beatDiv)
{
	return (nowPeriod - lastPeriod) * 60 / bpm * 4 * (numBeatDiv / beatDiv) * 1000;
}

void MusicScore::draw()
{
	for (auto& x : notes) x->draw();
	judge.draw();

#ifdef DEBUG
	DrawFormatString(800, 100, 0xffffff, "time:%d", timer.getElapsedTime());
#endif
}

void MusicScore::update()
{
	timer.update();
	judge.resetJudgedId();
	for (auto& x : notes) {
		//判定
		if (!x->getWasJudged()) {
			JudgeResult grade = judge.judge(x->getJudgeTiming(),
				                           timer.getElapsedTime(), 
				                           x->getJudgeTime(), 
				                           x->getTarget(),
				                           x->getTouchId());
			x->setJudge(grade);
		}

		x->setNowTime(timer.getElapsedTime());
		x->update();
	}
}
