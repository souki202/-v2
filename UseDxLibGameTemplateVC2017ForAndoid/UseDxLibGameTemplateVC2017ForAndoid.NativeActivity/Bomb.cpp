#include "Bomb.h"

BombResources::BombResources()
{
	rawImgs[0] = LoadGraph("Images/Play/Bomb/hit_circle.png");
	rawImgs[1] = LoadGraph("Images/Play/Bomb/hit_star.png");
	kiraImg = LoadGraph("Images/Play/Bomb/kira.png");
}

void Bomb::draw()
{
	for (auto& x : bombImgs) x.draw();
	for (auto& x : particle) {//パーティクルは軽量化のため,Imageを通さない.
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, x.alpha);
		float size = PARTICLE_SIZE * x.scale;
		DrawExtendGraphF(x.pos.first - size/2, x.pos.second - size/2,
			            x.pos.first + size/2, x.pos.second + size/2,
			            bombResources.getKiraImage(), true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

void Bomb::update()
{
	//ボム
	bombTimer.update();
	particleTimer.update();
	float scale = MyEase::easeOut(bombTimer.getElapsedTime(), BOMB_ANIM_TIME, 1.f, 1.75f);
	float alpha = MyEase::easeOut(bombTimer.getElapsedTime(), BOMB_ANIM_TIME, 0.f, 255.f);
	float alpha2 = MyEase::easeIn(bombTimer.getElapsedTime(), BOMB_ANIM_TIME, 255.f, 0.f);
	if (bombTimer.getElapsedTime() > BOMB_ANIM_TIME) {
		bombImgs[0].setImage(0);
		bombImgs[1].setImage(0);
	}
	bombImgs[0].setScale(scale, scale);
	bombImgs[0].setAlpha(static_cast<int>(alpha2));
	bombImgs[1].setAlpha(static_cast<int>(alpha));

	//パーティクル
	if (isStartParticle) {
		//新しく.
		particleElapsedTime += particleTimer.getDeltaTime();
		if (particleElapsedTime >= PARTICLE_INTERVAL) {
			particleElapsedTime -= PARTICLE_INTERVAL;
			//新規作成
			particle.push_back(ParticleInfo());
			particle.back().pos.first = rnd.generate(
				particleX - judgeLine.GET_JUDGE_SIZE() / 1.75,
				particleX + judgeLine.GET_JUDGE_SIZE() / 1.75
			);
		}
	}
	//更新ついでに終了したものを削除
	for (auto it = particle.begin(); it != particle.end();) {
		if (it->time > BOMB_ANIM_TIME) {
			it = particle.erase(it);
		}
		else {
			it->time += particleTimer.getDeltaTime();
			it->alpha = MyEase::easeIn(it->time, BOMB_ANIM_TIME, 255, 0);
			it->pos.second = judgeLine.GET_JUDGE_Y() - 125.f * it->time / BOMB_ANIM_TIME;
			++it;
		}
	}
}

void Bomb::startBomb(int line)
{
	if (isStartBomb) return;
	int x = judgeLine.getCenterPosition(line);
	for (int i = 0; i < 2; i++) {
		bombImgs[i].setImage(bombResources.getBombImage()[i]);
		bombImgs[i].setAlign(Align::Horizontal::CENTER, Align::Vertical::MIDDLE);
		bombImgs[i].setPosition(x, judgeLine.GET_JUDGE_Y());
	}
	bombImgs[1].setAlpha(0);
	bombTimer.reset();
	isStartBomb = true;
}
