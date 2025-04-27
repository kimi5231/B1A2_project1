#pragma once
#include "Creature.h"
#include "FlipbookActor.h"

class Flipbook;
class BoxCollider;
class ItemActor;
class ZipLine;
class LockedDoorAndKey;
class Window;
class FootHoldAndZipLineButton;
class DevScene;
class Projectile;

struct PlayerStat
{
	CommonStat commonStat{}; // A, B
	float runSpeed = 0;	// C
	float crouchSpeed = 0;	// D
	float jumpSpeed = 0;	// E
	int32 skillPoint = 0;	// F
	int32 nAtkRange = 0;	// G
	int32 nLongAtkDistance = 0;	// H
	int32 knockBackDistance = 0;	// I
	float strongAtkMultiplier = 0.f;	// J	
	int32 nAtkDamage = 0;	// K
	int32 skillDamage = 0;	// L
	int32 skillRange = 0;	// M
	float skillDuration = 0;	// N
	int32 skillStepDistance = 0;	// O

	void LoadFile(const std::wstring& path)
	{
		std::ifstream ifs;
		ifs.open(path);

		std::string line;

		if (std::getline(ifs, line))
		{
			std::istringstream lineStream(line);
			std::string cell;
			int column = 0;

			while (std::getline(lineStream, cell, ','))
			{
				switch (column)
				{
				case 0:this->commonStat.id = std::stoi(cell); break;	// A
				case 1: this->commonStat.hp = std::stoi(cell); break;	// B
				case 2: this->runSpeed = std::stof(cell); break;	// C
				case 3: this->crouchSpeed = std::stof(cell); break;	// D
				case 4: this->jumpSpeed = std::stof(cell); break;	// E
				case 5: this->skillPoint = std::stoi(cell); break;	// F
				case 6: this->nAtkRange = std::stoi(cell); break;	// G
				case 7: this->nLongAtkDistance = std::stoi(cell); break;	// H
				case 8: this->knockBackDistance = std::stoi(cell); break;	// I
				case 9: this->strongAtkMultiplier = std::stof(cell); break;	// J
				case 10: this->nAtkDamage = std::stoi(cell); break;	// K
				case 11: this->skillDamage = std::stoi(cell); break;	// L
				case 12: this->skillRange = std::stoi(cell); break;	// M
				case 13: this->skillDamage = std::stof(cell); break;	// N
				case 14: this->skillStepDistance = std::stoi(cell); break;	// O
				}
				++column;
			}
		}
		ifs.close();
	}
};

class Player : public Creature
{
	using Super = Creature;
public:
	Player();
	virtual ~Player() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

private:
	// Player State
	virtual void TickIdle() override;
	virtual void TickMove() override;
	virtual void TickDuckDown() override;
	virtual void TickDuckDownMove() override;
	virtual void TickJump() override;
	virtual void TickCloseAttack() override;
	virtual void TickLongAttack() override;
	virtual void TickSkillReady() override;
	virtual void TickSkillWaiting() override;
	virtual void TickSkillEnd() override;
	virtual void TickHang() override;
	virtual void TickRelease() override;
	virtual void TickHit() override;
	virtual void TickDead() override;
	virtual void UpdateAnimation() override;

public:
	virtual int32 GetAttack() override;
	virtual float GetSpeed() override;

	virtual void OnDamaged(Creature* other);
	void OnDamagedByProjectile(Projectile* projectile);

	// Hp 바뀔 때
	using HealthObserver = void(*)(int);	// hp 변화시 호출될 콜백 함수 타입
	void SetHealthObserver(std::function<void(int)> observer) { _healthObserver = observer; }
	
	void SetHealthPoint(int hp);
	void AddHealthPoint(int hp);
	void SubtractHealthPoint(int hp);

	int32& GetHp() { return _playerStat->commonStat.hp; }
	void SetHp(int32 hp) { _playerStat->commonStat.hp = hp; }

	int32 GetSkillPoint() { return _playerStat->skillPoint; }
	void SetSkillPoint(int32 skillPoint) { _playerStat->skillPoint = skillPoint; }
	void AddSkillPoint(int32 skillPoint) { _playerStat->skillPoint = min(5, _playerStat->skillPoint + skillPoint); }
	void SubtractSkillPoint(int32 skillPoint) { _playerStat->skillPoint = max(0, _playerStat->skillPoint - skillPoint); }

public:
	// Player가 Save Point에 충돌했을 때 스테이지 정보 저장을 위해 씬 정보가 필요함, 다른 씬 추가 시 수정 필요
	void SetCurrentScene(DevScene* devScene) { _devScene = devScene; }

public: 
	// 현실에서의 단위를 픽셀 단위로 바꿈
	void CalPixelPerSecond();

	// Collider
	void SetPlayerCollider(BoxCollider* collider) { _playerCollider = collider; }

	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other);
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other);
	
	void AdjustCollisionPos(BoxCollider* b1, BoxCollider* b2);	// 튕기기
	void TickGravity();

public:
	// Item
	void RemoveItem(int32 id, int32 count);
	std::unordered_map<int32, int32>& GetAquireItems() { return _acquiredItems; }
	void SetAcquireItems(const std::unordered_map<int32, int32>& items) { _acquiredItems = items; }		// 저장 데이터 불러올 때 사용
	void ClearAcquireItems() { _acquiredItems.clear(); }

public:
	int32 GetAtkRange() { return _playerStat->nAtkRange; }

	void SetIsCloseAtk(bool isCloseAtk) { _isCloseAtk = isCloseAtk; }

private:
	// Flipbook
	Flipbook* _flipbookPlayerIdle[2] = {};
	Flipbook* _flipbookPlayerMove[2] = {};
	Flipbook* _flipbookPlayerJump[2] = {};
	Flipbook* _flipbookPlayerDuckDown[2] = {};
	Flipbook* _flipbookPlayerDuckDownMove[2] = {};
	Flipbook* _flipbookPlayerHang[2] = {};
	Flipbook* _flipbookPlayerSlash[2] = {};		// CloseAtk

	Flipbook* _flipbookPlayerSkill[2] = {};
	//Flipbook* _flipbookPlayerCloseAttack[2] = {};
	//Flipbook* _flipbookPlayerLongAttack[2] = {};
	Flipbook* _flipbookPlayerRelease[2] = {};
	Flipbook* _flipbookPlayerHit[2] = {};
	Flipbook* _flipbookPlayerDead[2] = {};

private:
	bool _keyPressed = false;

	PlayerStat* _playerStat = {};

	std::function<void(int)> _healthObserver;	// 체력 변화 알림 받을 함수 포인터

	// Jump
	int32 _groundCollisionCount = 0;	// 충돌중인 타일맵 개수 (0개일 때 _Ground = true)
	int32 _gravity = 1000;
	float _ySpeed = {};

	bool _isGround = false;
	bool _isAir = false;

	// 획득한 아이템
	ItemActor* _collideItem = {};	// unordered map에 저장하기 위해, 충돌한 아이템을 담을 변수
	std::unordered_map<int32, int32> _acquiredItems;		// [아이템 ID, 개수]

	DevScene* _devScene = nullptr;	// 현재 씬 데이터 정보 저장을 위해 필요, 다른 게임 Scene 추가시 수정 필요

	ZipLine* _zipLine = nullptr;	// 충돌 중인 짚라인의 정보를 가져와서 매달리기
	Window* _window = nullptr;
	FootHoldAndZipLineButton* _footHoldAndZipLineButton = nullptr;

	BoxCollider* _playerCollider = nullptr;
	Collider* _attackCollider = nullptr;
	Collider* _detectCollider = nullptr;	// 근거리, 원거리 공격 결정 

	bool _isCloseAtk = false;
	bool _isKeyAcquire = false;
	bool _isInWindow = false;
	bool _damagedByWindow = false;	
	bool _isReleaseInMid = false;

	// Skill
	float _skillTimer = 0.f;
	int32 _leftInputCount = 0;
	int32 _rightInputCount = 0;
};

