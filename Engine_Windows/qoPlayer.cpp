#include "qoPlayer.h"
#include "qoGun.h"
#include "qoGunScript.h"
#include "qoSuperpositionGunScript.h"
#include "qoTransform.h"
#include "qoMeshRenderer.h"
#include "qoResourceManager.h"
#include "qoSuperpositionGun.h"

namespace qo
{
	Player::Player()
		: mGuns{}
		, mActiveGun(nullptr)
		, mState(ePlayerState::Idle)
		, mHp(100)
		, mSpeed(1.f)
	{
	}

	Player::~Player()
	{
		// 플레이어 소멸시 플레이어가 관리하던 Guns 메모리 해제
		for (Gun* gun : mGuns)
		{
			if (gun != nullptr)
			{
				delete gun;
				gun = nullptr;
			}
		}
	}

	void Player::Initialize()
	{
		GameObject::Initialize();
	}

	void Player::Update()
	{
		GameObject::Update();

		// 현재 활성화 되어있는 총만 Update 시켜준다.
		if (mActiveGun != nullptr)
		{
			mActiveGun->Update();
		}
	}

	void Player::LateUpdate()
	{
		GameObject::LateUpdate();

		// 현재 활성화 되어있는 총만 LateUpdate 시켜준다.
		if (mActiveGun != nullptr)
		{
			mActiveGun->LateUpdate();
		}
	}

	void Player::Render()
	{
		GameObject::Render();

		// 현재 활성화 되어있는 총만 Render 시켜준다.
		if (mActiveGun != nullptr)
		{
			mActiveGun->Render();
		}
	}

	void Player::AddGun(eGunType type)
	{
		// 플레이어 객체 정보
		Transform* PlayerTransform = GetComponent<Transform>();
		Vector3 PlayerPos = PlayerTransform->GetPosition();

		// ================================
		// 총 객체 생성
		// ================================
		if (type == eGunType::Superposition)
		{
			SuperpositionGun* gun = new SuperpositionGun(type, this, 10);
			Vector3 GunPos = PlayerPos + Vector3(0.2f, 0.f, 0.f);

			Transform* GunTransform = gun->AddComponent<Transform>();
			GunTransform->SetPosition(GunPos);
			GunTransform->SetScale(Vector3(0.1f, 0.1f, 0.f));
			GunTransform->SetColor(gun->GetGunColor());

			MeshRenderer* meshRenderer = gun->AddComponent<MeshRenderer>();
			meshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"RectangleMesh"));
			meshRenderer->SetShader(ResourceManager::Find<Shader>(L"ColorTestShader"));

			gun->AddComponent<GunScript>();
			gun->AddComponent<SuperpositionGunScript>();

			gun->Initialize();

			mGuns.push_back(gun);
			mActiveGun = gun;
		}
		else if(type == eGunType::Entanglement)
		{

		}
		else if (type == eGunType::Teleportation)
		{

		}
	}

	void Player::TakeHit(int DamageAmount, math::Vector3 HitDir)
	{
	}
}