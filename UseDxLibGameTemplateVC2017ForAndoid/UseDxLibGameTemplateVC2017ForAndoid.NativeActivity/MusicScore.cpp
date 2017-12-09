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
	int divPeriod = 4; //���ߕ�����
	int numBeatDiv = 4; // div����numDiv���q
	int beatDiv = 4;
	std::map<int, int> useId; //id, uid(�z��ԍ�) LN�ȊO
	std::map<int, int> useLnId; //line, uid LN��p
	int uid = 0;

	judgeLine.setNumLine(5);

	while (std::getline(ifs, line)) {
		//�R�����g�s
		if (line.size() >= 2) {
			if (line[0] == '/' && line[1] == '/') continue;
		}

		//���s
		//�Ȃ̎��Ԃ͉��Z���Ȃ�
		if (!line.empty() && line.front() == '#') {
			line = line.substr(1);
			std::stringstream ss(line);

			//�����������擾
			std::string tmp;
			std::vector<std::string> args;
			while (std::getline(ss, tmp, ' ')) {
				args.push_back(tmp);
			}

			if (args[0] == "BPM") {
				bpm = std::atof(args[1].c_str());
				//�s���I�h�o�ߐ����X�V
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
			else if (std::isdigit(args[0][0])) { //���ߐ��X�L�b�v
				lastPeriod = nowPeriod;
				nowPeriod = std::atof(args[0].c_str());
				divPeriod = std::atoi(args[1].c_str());
				nowTime += calcElapsedTime(lastPeriod, nowPeriod, bpm, numBeatDiv, beatDiv);
			}
			continue;
		}

		//���ʍs
		std::stringstream ss(line);
		//���ʂȂ��̍s
		if(line.empty()) {}
		else { //���ʂ���
			std::vector<std::string> noteInfo;
			std::string noteStr;
			int no = 0;
			while (std::getline(ss, noteStr, '\t')) {
				//�m�[�g��񂠂�
				if (!noteStr.empty() && noteStr.front() != '-') {
					//�������擾
					std::stringstream ss2(noteStr);
					std::vector<float> args;
					while (std::getline(ss2, noteStr)) {
						args.push_back(std::atof(noteStr.c_str()));
					}

					//�m�[�g�ݒ�
					float appear = no;
					NoteType type;
					int id = 0;
					int endPoint = false; //LN���̏I�_
					type = static_cast<NoteType>(static_cast<int>(args[0]));
					if (args.size() >= 2) appear = args[1];
					if (args.size() >= 3) id = static_cast<int>(args[2]);
					if (args.size() >= 4) endPoint = true;


					//�^�C�v�ݒ�
					//FLICK��LN,SLIDE�I�_�ȊO�����ݒ�
					std::shared_ptr<Note> lastNote;
					//�O�̃m�[�g������Ȃ炻��𗘗p���邽�ߕۑ�
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
							//��芸�����˂�����ǂ�
							flickNote->setDirection(direction);
							//�O��̃m�[�g�ƏƂ炵���킹�ăt���b�N����������
							if (lastNote) {
								lastNote->setDirectionByNextNote(flickNote);
								flickNote->setDirectionByLastNote(lastNote);
							}
							haveNextNote = std::move(flickNote);
						}
						break;
						default: break;
						}

						//��O�̃m�[�g�ɐڑ�����m�[�g��ݒ�
						if (lastNote) {
							lastNote->setNextNote(haveNextNote);
						}
						note = std::move(haveNextNote);

						//���̃m�[�g���X�V
						if (NoteType::LN < type && type <= NoteType::FLICK_R) {
							useId[id] = uid;
						}
						if (type == NoteType::LN) {
							useLnId[no] = uid;
						}

						//id�J�� ���ʂ�LN�͐ڑ��悪���ꂽ�狭���I�ɊJ��
						if (endPoint && (type != NoteType::LN)) {
							useId.erase(id);
						}
						else if ((endPoint || lastNote) && type == NoteType::LN) {
							useLnId.erase(no);
						}
					}

					//�ėp�ݒ肵�Ēǉ�
					note->setting(no, appear, nowTime, uid, id);
					notes.push_back(std::move(note));

					//�z��ԍ���i�߂�
					uid++;
				}
				no++;
			}
		}

		//�o�߃s���I�h�����X�V
		lastPeriod = nowPeriod;
		nowPeriod += 1.0 / divPeriod / (numBeatDiv / beatDiv);
		nowTime += calcElapsedTime(lastPeriod, nowPeriod, bpm, numBeatDiv, beatDiv);
		continue;
	}

	//�m�[�g�����ԏ��Ƀ\�[�g
	std::sort(notes.begin(), notes.end(), 
			  [](const std::shared_ptr<Note>& l, const std::shared_ptr<Note>& r) {
					return l->getJudgeTime() > r->getJudgeTime(); 
			  }
	);

	judgeLine.loadJudgeIcons();
	//���y�ǂݍ���
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
		//����
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
