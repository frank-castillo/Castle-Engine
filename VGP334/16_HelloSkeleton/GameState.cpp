#include "GameState.h"
#include "Input/Inc/InputSystem.h"

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 1.0f, -3.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

	mDirectionalLight.direction = Normalize({ 1.0f,-1.0f, 1.0f });
	mDirectionalLight.ambient = { 0.8f, 0.8f, 0.8f, 1.0f };
	mDirectionalLight.diffuse = { 0.7f, 0.7f, 0.7f, 1.0f };
	mDirectionalLight.specular = { 0.7f, 0.7f, 0.7f, 1.0f };

	Mesh ground = MeshBuilder::CreatePlane(20, 20, 1.0f);
	mGround.meshBuffer.Initialize(ground);
	mGround.diffuseMapId = TextureManager::Get()->LoadTexture(L"Textures/misc/concrete.jpg");
	mGround.material.ambient = { 0.8f, 0.8f, 0.8f, 1.0f };
	mGround.material.diffuse = { 0.8f, 0.8f, 0.8f, 1.0f };
	mGround.material.specular = { 0.8f, 0.8f, 0.8f, 1.0f };
	mGround.material.power = {1.0f};
	mGround.transform.position.y = -1.0f;

	Mesh sphere = MeshBuilder::CreateSphere(20, 20, 1.0f);
	mSphere.meshBuffer.Initialize(sphere);
	mSphere.diffuseMapId = TextureManager::Get()->LoadTexture(L"Textures/planets/mars.jpg");
	mSphere.material.ambient = { 0.8f, 0.8f, 0.8f, 1.0f };
	mSphere.material.diffuse = { 0.8f, 0.8f, 0.8f, 1.0f };
	mSphere.material.specular = { 0.8f, 0.8f, 0.8f, 1.0f };
	mSphere.material.power = { 1.0f };
	mSphere.transform.position.y = 0.0f;

	mStandardEffect.Initialize(L"../../Assets/Shaders/Standard.fx");
	mStandardEffect.SetCamera(mCamera);
	mStandardEffect.SetDirectionalLight(mDirectionalLight);

	mAnimationTime = 0.0f;
	mSphereAnimation = AnimationBuilder()
		.AddPositionKey(Vector3(0.0f, 2.0f, 0.0f), 0.0f, Linear)
		.AddPositionKey(Vector3(0.0f, 0.5f, 0.0f), 0.5f, Linear)
		.AddPositionKey(Vector3(0.0f, 0.0f, 0.0f), 1.0f, Linear)

		.AddScaleKey(Vector3(1.0f, 1.0f, 1.0f), 1.0f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(0.0f, 0.0f, 0.0f), 1.0f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(0.5f, 0.0f, 0.0f), 2.0f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(1.0f, 0.0f, 0.0f), 3.0f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(1.5f, 0.0f, 0.0f), 4.0f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(2.0f, 0.0f, 0.0f), 5.0f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(3.0f, 0.0f, 0.0f), 5.5f, EaseInQuad)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(4.0f, 0.0f, 0.0f), 6.0f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(5.0f, 0.0f, 0.0f), 6.5f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(6.0f, 0.0f, 0.0f), 7.0f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(7.0f, 0.0f, 0.0f), 7.4f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(8.0f, 0.0f, 0.0f), 7.8f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(9.0f, 0.0f, 0.0f), 8.0f, EaseInQuad)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(10.0f, 0.0f, 0.0f), 8.2f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(11.0f, 0.0f, 0.0f), 8.4f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(12.0f, 0.0f, 0.0f), 8.6f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(13.0f, 0.0f, 0.0f), 8.8f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(14.0f, 0.0f, 0.0f), 9.0f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(15.0f, 0.0f, 0.0f), 9.2f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(16.0f, 0.0f, 0.0f), 9.4f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(17.0f, 0.0f, 0.0f), 9.6f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(18.0f, 0.0f, 0.0f), 9.8f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(19.0f, 0.0f, 0.0f), 10.0f, EaseInQuad)
		.AddScaleKey(Vector3(1.0f, 1.0f, 1.0f), 10.0f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(20.0f, 0.0f, 0.0f), 10.1f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(21.0f, 0.0f, 0.0f), 10.2f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(22.0f, 0.0f, 0.0f), 10.3f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(23.0f, 0.0f, 0.0f), 10.4f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(24.0f, 0.0f, 0.0f), 10.5f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(25.0f, 0.0f, 0.0f), 10.6f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(26.0f, 0.0f, 0.0f), 10.7f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(27.0f, 0.0f, 0.0f), 10.8f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(28.0f, 0.0f, 0.0f), 10.9f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(29.0f, 0.0f, 0.0f), 11.0f, EaseInQuad)
		.AddScaleKey(Vector3(1.0f, 0.8f, 1.0f), 11.0f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(30.0f, 0.0f, 0.0f), 11.05f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(31.0f, 0.0f, 0.0f), 11.10f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(32.0f, 0.0f, 0.0f), 11.15f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(33.0f, 0.0f, 0.0f), 11.20f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(34.0f, 0.0f, 0.0f), 11.25f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(35.0f, 0.0f, 0.0f), 11.30f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(36.0f, 0.0f, 0.0f), 11.35f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(37.0f, 0.0f, 0.0f), 11.40f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(38.0f, 0.0f, 0.0f), 11.45f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(39.0f, 0.0f, 0.0f), 11.50f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(40.0f, 0.0f, 0.0f), 11.52f, EaseInQuad)
		.AddScaleKey(Vector3(1.0f, 0.6f, 1.0f), 11.52f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(41.0f, 0.0f, 0.0f), 11.54f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(42.0f, 0.0f, 0.0f), 11.56f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(43.0f, 0.0f, 0.0f), 11.58f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(44.0f, 0.0f, 0.0f), 11.60f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(45.0f, 0.0f, 0.0f), 11.62f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(46.0f, 0.0f, 0.0f), 11.64f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(47.0f, 0.0f, 0.0f), 11.66f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(48.0f, 0.0f, 0.0f), 11.68f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(49.0f, 0.0f, 0.0f), 11.70f, Linear)
		.AddScaleKey(Vector3(1.0f, 0.4f, 1.0f), 11.70f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(50.0f, 0.0f, 0.0f), 11.71f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(51.0f, 0.0f, 0.0f), 11.72f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(52.0f, 0.0f, 0.0f), 11.73f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(53.0f, 0.0f, 0.0f), 11.74f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(54.0f, 0.0f, 0.0f), 11.75f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(55.0f, 0.0f, 0.0f), 11.76f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(56.0f, 0.0f, 0.0f), 11.77f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(57.0f, 0.0f, 0.0f), 11.78f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(58.0f, 0.0f, 0.0f), 11.79f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(59.0f, 0.0f, 0.0f), 11.80f, Linear)
		.AddScaleKey(Vector3(0.6f, 0.2f, 0.6f), 11.80f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(60.0f, 0.0f, 0.0f), 11.81f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(61.0f, 0.0f, 0.0f), 11.82f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(62.0f, 0.0f, 0.0f), 11.83f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(63.0f, 0.0f, 0.0f), 11.84f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(64.0f, 0.0f, 0.0f), 11.85f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(65.0f, 0.0f, 0.0f), 11.86f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(66.0f, 0.0f, 0.0f), 11.87f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(67.0f, 0.0f, 0.0f), 11.88f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(68.0f, 0.0f, 0.0f), 11.89f, Linear)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(69.0f, 0.0f, 0.0f), 11.90f, Linear)
		.AddScaleKey(Vector3(0.0f, 0.0f, 0.0f), 11.90f, Linear)
		.AddScaleKey(Vector3(0.0f, 0.0f, 0.0f), 12.0f, Linear)
		.AddScaleKey(Vector3(0.0f, 0.0f, 0.0f), 13.0f, Linear)
		.AddPositionKey(Vector3(0.0f, 0.0f, 0.0f), 13.0f, Linear)
		.AddPositionKey(Vector3(0.0f, 2.0f, 0.0f), 13.50f, Linear)
		.AddScaleKey(Vector3(1.0f, 1.0f, 1.0f), 13.50f, Linear)

		.Build();
}

void GameState::Terminate()
{
	mStandardEffect.Terminate();
	mSphere.Terminate();
	mGround.Terminate();
}

void GameState::Update(float deltaTime)
{
	auto input = InputSystem::Get();
	const float moveSpeed = input->IsKeyDown(KeyCode::LSHIFT) ? 10.0f : 1.0f;
	const float turnSpeed = 0.1f;
	const float modelTurnSpeed = 0.5f;

	if (input->IsKeyDown(KeyCode::W))
	{
		mCamera.Walk(moveSpeed * deltaTime);
	}
	else if (input->IsKeyDown(KeyCode::S))
	{
		mCamera.Walk(-moveSpeed * deltaTime);
	}

	if (input->IsKeyDown(KeyCode::A))
	{
		mCamera.Strafe(-moveSpeed * deltaTime);
	}
	else if (input->IsKeyDown(KeyCode::D))
	{
		mCamera.Strafe(moveSpeed * deltaTime);
	}

	if (input->IsKeyDown(KeyCode::E))
	{
		mCamera.Rise(moveSpeed * deltaTime);
	}
	else if (input->IsKeyDown(KeyCode::Q))
	{
		mCamera.Rise(-moveSpeed * deltaTime);
	}

	if (input->IsMouseDown(MouseButton::RBUTTON))
	{
		mCamera.Yaw(input->GetMouseMoveX() * turnSpeed * deltaTime);
		mCamera.Pitch(input->GetMouseMoveY() * turnSpeed * deltaTime);
	}

	mAnimationTime += deltaTime;
	const float animDuration = mSphereAnimation.GetDuration();

	while (mAnimationTime > animDuration)
	{
		mAnimationTime -= animDuration;
	}

	mSphere.transform = mSphereAnimation.GetTransform(mAnimationTime);
}

void GameState::Render()
{
	mStandardEffect.Begin();
		mStandardEffect.Render(mGround);
		mStandardEffect.Render(mSphere);
	mStandardEffect.End();
}

void GameState::DebugUI()
{
	ImGui::Begin("Debug Controls", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Separator();

	if (ImGui::CollapsingHeader("Light", ImGuiTreeNodeFlags_DefaultOpen))
	{
		if (ImGui::DragFloat3("Direction##Light", &mDirectionalLight.direction.x, 0.01f, -1.0f, 1.0f))
		{
			mDirectionalLight.direction = Normalize(mDirectionalLight.direction);
		}

		ImGui::ColorEdit4("Ambient##Light", &mDirectionalLight.ambient.r);
		ImGui::ColorEdit4("Diffuse##Light", &mDirectionalLight.diffuse.r);
		ImGui::ColorEdit4("Specular##Light", &mDirectionalLight.specular.r);
	}

	ImGui::Separator();

	mStandardEffect.DebugUI();

	ImGui::End();
}