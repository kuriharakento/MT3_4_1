#include <imgui.h>
#include <Novice.h>
#include "MyFunctions.h"

const char kWindowTitle[] = "LC1A_13_クリハラ_ケント_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Sphere sphere
	{
		{0,0,0},
		0.08f
	};

	Vector3 center = { 0.0f,0,0 };
	float radius = 1.0f;

	unsigned int color = WHITE;

	float angularVelocity = 3.14f;
	float angle = 0.0f;
	float deltaTime = 1.0f / 60.0f;

	bool isStart = false;

	Vector3 cameraTranslate{ 0.0f,1.9f,-6.49f };
	Vector3 cameraRotate{ 0.26f,0.0f,0.0f };

	float cameraSpeed = 0.01f;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		if (keys[DIK_W])
		{
			cameraTranslate.z += cameraSpeed;
		}
		if (keys[DIK_S])
		{
			cameraTranslate.z -= cameraSpeed;
		}
		if (keys[DIK_A])
		{
			cameraTranslate.x -= cameraSpeed;
		}
		if (keys[DIK_D])
		{
			cameraTranslate.x += cameraSpeed;
		}
		if (keys[DIK_Q])
		{
			cameraTranslate.y += cameraSpeed;
		}
		if (keys[DIK_E])
		{
			cameraTranslate.y -= cameraSpeed;
		}

		Matrix4x4 cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraTranslate);
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, (float)kWindowWidth / (float)kWindowHeight, 0.1f, 100.0f);
		Matrix4x4 viewProjectionMatrix = Multiply(viewMatrix, projectionMatrix);
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, (float)kWindowWidth, (float)kWindowHeight, 0.0f, 1.0f);


		if (isStart)
		{
			angle += angularVelocity * deltaTime;
		}


		sphere.center.x = center.x + std::cos(angle) * radius;
		sphere.center.y = center.y + std::sin(angle) * radius;
		sphere.center.z = center.z;


		ImGui::Begin("window");


		ImGui::Text("camera");
		ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);

		ImGui::Text("setting");

		if (ImGui::Button("start"))
		{
			isStart = true;
		}


		ImGui::End();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(viewProjectionMatrix, viewportMatrix);
		DrawSphere(sphere, viewProjectionMatrix, viewportMatrix, color);

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
