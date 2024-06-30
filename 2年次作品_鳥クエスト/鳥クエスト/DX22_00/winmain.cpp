#undef UNICODE  // Unicodeではなく、マルチバイト文字を使う

#include <Windows.h>
#include "Direct3d.h"
#include "input.h"
#include <DirectXMath.h>
#include "WICTextureLoader.h"
#include "ObjModelLoader.h"
#include "Model.h"
#include "BackCamera.h"
#include "NormalObject.h"
#include "Explosion.h"
#include <map> // 連想配列
#include <vector> // 可変配列
#include <time.h>
#include	<iomanip>
#include	"Csv.h"
#include "AI.h"
#include "Cho.h"
#include "stdio.h"
#include <time.h>
#include <Windows.h>
#include <stdlib.h>
#include <iostream>

#pragma comment (lib, "winmm.lib") // timeGetTime関数のため

// マクロ定義
#define CLASS_NAME    "DX21Smpl"// ウインドウクラスの名前
#define WINDOW_NAME  "スケルトンプログラム"// ウィンドウの名前

#define SCREEN_WIDTH (1024)	// ウインドウの幅
#define SCREEN_HEIGHT (576+30)	// ウインドウの高さ


#define SPEED         (0.004) //スピード
#define CHANGESPEED  (0.30) //方向転換時の速度
#define BIRUSUU      (36)   //ビルの数
#define BIRU2SUU     (1)   //ビル2の数
#define CHARASUU     (30)  //キャラ数
#define YUKISUU      (800)  //雪の数
#define YUKIHANI     (70)   //雪を降らす範囲
#define YUKISPEED    (0.05)  //雪を降らすスピード
#define YUKITAKASA     (10)
#define KUSASUU       (100)  //草の数
#define DISKSUU        (100)  //ディスクの数
#define SUJISUU         (13)  //数字の数
#define SUJIHYOUJI       (6)  //表示する数字の数
#define SUJIUV          (0.0769230769230769)
#define TIMELIMIT       (180)
#define TORIHP           (3)
#define TORIX             (-3.5)     //鳥の初期X
#define TORIY             (1.0)     //鳥の初期Y
#define TORIZ             (-3.5)     //鳥の初期Z
#define TORIROTEY         (90)       //鳥の初期角度Y
#define TORIROTEZ           (0)       //鳥の初期角度Z
#define MUTEKI             (5)        //無敵時間
#define TAKASA             (7)
#define RIAL                (4)      //チュートリアルの数
#define STARTCOUNT           (5)    //カウントダウン
#define TEKISUU              (10)   //敵の数
#define BIRUMAYOKO           (5)
#define BIRUMATATE            (5)



// 構造体の定義


// 関数のプロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// ゲームの画面描画の関数
void Game_Init();
void Game_Draw();
void Game_Update();
void Game_Release();

void TitleUpdate();
void StageUpdate();
void ResultUpdate();
void SerectUpdate();
void TyutoUpdate();

void Set(GameObject* a, bool b, float _c, float _d, float _e, float _f);


// 画面遷移関連
enum SCENE_ID
{
	NONE,  // どの画面でもない
	TITLE, // タイトル画面
	STAGE, // ステージ画面
	RESULT, //　リザルト画面
	SERECT,  //セレクト画面
	TYUTORIAL
};

enum CLEAR_ID
{
	NONE2,         //どの画面でもない
	CLEAR,        //クリア画面
	GAMEOVER,     //ゲームオーバー画面
};

enum SERECT_ID
{
	NONE3,  //どの画面でもない
	GAME,   //ゲーム
	TYUTO,  //チュートリアル
};



SCENE_ID gNowScene = TITLE;         //今の画面IDを持つ変数

SCENE_ID gmaeScene = TITLE;         //前の画面IDを持つ変数

CLEAR_ID gresult = NONE2;

SERECT_ID gsere = NONE3;


int tensuu;


// グローバル変数の宣言

// 頂点バッファ用の変数
ID3D11Buffer* gpVertexBuffer;

// 頂点数を持つ変数
int gNumVertex;

// テクスチャ用の変数
ID3D11ShaderResourceView* gpTextureHalOsaka; // HAL OSAKA


extern ID3D11Buffer* gpConstBuffer;

using namespace DirectX;

// GameObjectクラスの変数
GameObject* gpCottage;
GameObject* gptori;
GameObject* gpShot;
GameObject* gp2Dchar[CHARASUU];
GameObject* gpShadow;
GameObject* gpori;
GameObject* gpbiru[BIRUSUU];
GameObject* gpbiru2[BIRU2SUU];
GameObject* gpsora;
GameObject* gpdisk[DISKSUU];
GameObject* gpyuki[YUKISUU];
GameObject* gpkusa;
GameObject* title;
GameObject* aicon;
GameObject* plessen;
GameObject* suji[SUJISUU][SUJIHYOUJI];
GameObject* watch;
GameObject* gameover;
GameObject* clear;
GameObject* gamestart;
GameObject* tyutori;
GameObject* yajirusi;
GameObject* serect;
GameObject* tyuto[RIAL];
GameObject* gpteki[TEKISUU];

typedef std::vector<GameObject*> GameObjectVector;

GameObjectVector gObjectList;

#define MAX_GROUND  30
GameObject* gpGround[MAX_GROUND][MAX_GROUND];

// 弾管理用配列
GameObjectVector gShotManager;

// エフェクト管理用配列
GameObjectVector gEffectManager;

// モデルマネージャー
// 連想配列＝添え字に整数以外も使える配列
// テンプレート＝使うときに内部の型を決める
// mapの場合、前が添え字型、後ろが格納する要素の型
std::map<std::string, ModelData> gModelManager;


// Cameraクラスの変数
Camera* gpCamera;

// デルタタイム用の変数
DWORD gDeltaTime;

//画面用変数
#include "SceneTitle.h"

IScene* gpActiveScene = new SceneTitle();

#define NMAX   (64)             //座標を格納する最大値     


int CI::map[10][10];
int CI::flag[MAPX][MAPY];


void vector_DrawAll(GameObjectVector vec)
{
	for (auto e : vec)
	{
		e->Draw();
	}
}

void vector_UpdateAll(GameObjectVector vec)
{
	for (auto e : vec)
	{
		e->Update();
	}
}

void vector_DeleteAll(GameObjectVector vec)
{
	for (auto e : vec)
	{
		delete e;
	}

	vec.clear();
}

// ビルボード用のポリゴンを作成し、テクスチャも読み込む
ModelData CreateSquarePolygon(float width, float height, float uvlowwidth,float uvlow,float uvWidth, float uvHeight, const wchar_t* texFile)
{
	// モデル頂点データ作成
	const float w = width / 2.0f;
	const float h = height / 2.0f;
	ModelVertex vx[] = {
		{ -w,  h, 0, uvlowwidth, uvlow },
		{  w,  h, 0, uvWidth, uvlow },
		{  w, -h, 0, uvWidth, uvHeight },

		{  w, -h, 0, uvWidth, uvHeight },
		{ -w, -h, 0, uvlowwidth, uvHeight },
		{ -w,  h, 0, uvlowwidth, uvlow },
	};

	vx[0].u = uvlowwidth;
	vx[0].v = uvlow;
	vx[1].u = uvWidth;
	vx[1].v = uvlow;
	vx[2].u = uvWidth;
	vx[2].v = uvHeight;
	vx[3].u = uvWidth;
	vx[3].v = uvHeight;
	vx[4].u = uvlowwidth;
	vx[4].v = uvHeight;
	vx[5].u = uvlowwidth;
	vx[5].v = uvlow;

	ModelData modelData;

	modelData.mNumVertex = sizeof(vx) / sizeof(ModelVertex); // 頂点数を計算

	// モデル用の頂点バッファ作成
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.ByteWidth = sizeof(vx);
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	// バッファの初期値指定
	D3D11_SUBRESOURCE_DATA initialVertexData;
	// 頂点バッファの初期値
	initialVertexData.pSysMem = vx;
	// 頂点バッファでは使用しない
	initialVertexData.SysMemPitch = 0;
	initialVertexData.SysMemSlicePitch = 0;

	HRESULT hr = Direct3D_Get()->device->CreateBuffer(&bufferDesc, &initialVertexData, &modelData.mVertexBuffer);

	if (FAILED(hr))
	{
		throw hr;
	}

	Direct3D_LoadTexture(texFile, &modelData.mSRV);

	return modelData;
}

// WinMain関数を作る
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	srand((unsigned)time(nullptr));

	WNDCLASSEX wc; // WND = Window

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_CLASSDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc); // Windowsにウインドウ情報を登録

	HWND hWnd; // H=Handle=ポインタ WND=Window
	hWnd = CreateWindowEx(0,// 拡張ウィンドウスタイル
		CLASS_NAME,// ウィンドウクラスの名前
		WINDOW_NAME,// ウィンドウの名前
		WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,// ウィンドウスタイル
		CW_USEDEFAULT,// ウィンドウの左上Ｘ座標
		CW_USEDEFAULT,// ウィンドウの左上Ｙ座標 
		SCREEN_WIDTH,// ウィンドウの幅
		SCREEN_HEIGHT,// ウィンドウの高さ
		NULL,// 親ウィンドウのハンドル
		NULL,// メニューハンドルまたは子ウィンドウID
		hInstance,// インスタンスハンドル
		NULL);// ウィンドウ作成データ

	// 指定されたウィンドウの表示状態を設定(ウィンドウを表示)
	ShowWindow(hWnd, nCmdShow);
	// ウィンドウの状態を直ちに反映(ウィンドウのクライアント領域を更新)
	UpdateWindow(hWnd);

	// Direct3Dの初期化関数を呼び出す
	Direct3D_Init(hWnd);

	Game_Init();

	

	MSG msg;
	// メインループ
	for (;;) {
		// 前回のループからユーザー操作があったか調べる
		BOOL doesMessageExist = PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);

		if (doesMessageExist)
		{
			// 間接的にウインドウプロシージャを呼び出す
			DispatchMessage(&msg);

			// アプリ終了命令が来た
			if (msg.message == WM_QUIT) {
				break;
			}
		}
		else
		{
			// デルタタイムの計測
			static DWORD lastTime = timeGetTime(); // 前回計測時の時間
			timeBeginPeriod(1); // 精度を１ミリ秒に上げる
			DWORD nowTime = timeGetTime(); // 現在の時間
			timeEndPeriod(1); // 精度を元に戻す
			gDeltaTime = nowTime - lastTime; // 差分がデルタタイム
			lastTime = nowTime; // 前回計測時間として保存

			// ゲームループ
			Game_Update(); // ゲーム処理
			Game_Draw();   // ゲーム描画
			Input_Refresh(); // キー状態の更新
		}
	}

	Game_Release();
	// Direct3Dの解放関数を呼び出す
	Direct3D_Release();

	UnregisterClass(CLASS_NAME, hInstance);

	return (int)msg.wParam;
}


// ウインドウプロシージャ関数を作る
// ※関数を作れるのはグローバル領域(=どの関数の中でもない場所)だけ！
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// uMsg（この関数の第2引数）が、ユーザー操作のID情報
	switch (uMsg)
	{
	case WM_DESTROY:// ウィンドウ破棄のメッセージ
		PostQuitMessage(0);// “WM_QUIT”メッセージを送る　→　アプリ終了
		break;

	case WM_CLOSE:  // xボタンが押されたら
		DestroyWindow(hWnd);  // “WM_DESTROY”メッセージを送る
		break;

	case WM_LBUTTONDOWN: // 左クリックされたとき
		Input_SetKeyDown(VK_LBUTTON);
		break;

	case WM_LBUTTONUP: // 左クリックされたとき
		Input_SetKeyUp(VK_LBUTTON);
		break;

	case WM_RBUTTONDOWN: // 左クリックされたとき
		Input_SetKeyDown(VK_RBUTTON);
		break;

	case WM_RBUTTONUP: // 左クリックされたとき
		Input_SetKeyUp(VK_RBUTTON);
		break;

	case WM_MOUSEMOVE: // マウスカーソルが動いたとき
		break;

	case WM_KEYDOWN:
		// キーが押された時のリアクションを書く
		// ESCが押されたのかどうかチェック
		if (LOWORD(wParam) == VK_ESCAPE)
		{
			// メッセージボックスで修了確認
			int result;
			result = MessageBox(NULL, "終了してよろしいですか？",
				"終了確認", MB_YESNO | MB_ICONQUESTION);
			if (result == IDYES) // 「はい」ボタンが押された時
			{
				// xボタンが押されたのと同じ効果を発揮する
				PostMessage(hWnd, WM_CLOSE, wParam, lParam);
			}
		}
		Input_SetKeyDown(LOWORD(wParam));
		break;

	case WM_KEYUP: // キーが離されたイベント
		Input_SetKeyUp(LOWORD(wParam));
		break;

	default:
		// 上のcase以外の場合の処理を実行
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
		break;
	}

	return 0;
}

void Game_Init()
{
	// 定数バッファ作成
	// コンスタントバッファとして作成するための情報設定
	D3D11_BUFFER_DESC contstat_buffer_desc;
	contstat_buffer_desc.ByteWidth = 512;	// バッファのサイズ（4x4行列x4個）
	contstat_buffer_desc.Usage = D3D11_USAGE_DYNAMIC;		// 使用方法
	contstat_buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;	// バッファの種類(コンスタントバッファ)
	contstat_buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;			// CPUアクセス設定
	contstat_buffer_desc.MiscFlags = 0;				// その他のオプション
	contstat_buffer_desc.StructureByteStride = 0;			// 構造体サイズ(行列を使うが今回は0でも動作することを実証する)

	Direct3D_Get()->device->CreateBuffer(&contstat_buffer_desc,
		nullptr, &gpConstBuffer);

	// カメラの作成
	gpCamera = new BackCamera();
	Camera::mMainCamera = gpCamera;
	// 初期値設定
	// 注意：eyeとfocusが同じだとダメ
	// 注意：upのxyz全てゼロだとダメ
	gpCamera->SetEye(XMFLOAT3(0.0f, 0.0f, -2.0f));
	gpCamera->SetFocus(XMFLOAT3(0.0f, 0.0f, 0.0f));
	gpCamera->SetUp(XMFLOAT3(0.0f, 1.0f, 0.0f));


	int map3[MAPX][MAPY] = {
{0,1,1,1,1,1,1,1,1,0},
{0,0,0,0,0,0,0,0,0,0},
{0,1,1,0,1,1,1,0,0,0},
{0,0,0,0,1,1,1,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,1,0,1,1,0,1,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,1,1,1,1,1,1,1,1,0},
{0,1,1,1,1,1,1,1,1,0},
{0,0,0,0,0,0,0,0,0,0},
	};

	CI::Setmap(map3);   //マップ情報をセット


	// モデル読み込み
	ObjModelLoader loader;
	gModelManager["cottage"] = loader.Load(
		"assets/cottage.obj", L"assets/cottage.png");

	// 鳥モデル読み込み
	loader = ObjModelLoader();
	gModelManager["gun"] = loader.Load(
		"assets/tori.obj", L"assets/ステンレス.jpg");

	loader = ObjModelLoader();
	gModelManager["teki"] = loader.Load(
		"assets/teki.obj", L"assets/ステンレス.jpg");

	//ビルモデル読み込み
	loader = ObjModelLoader();
	gModelManager["biru"] = loader.Load(
		"assets/biru.obj", L"assets/コンクリート2.jpg");

	//檻モデル読み込み
	loader = ObjModelLoader();
	gModelManager["ori"] = loader.Load(
		"assets/ori.obj", L"assets/ステンレス.jpg");

	//ビル2モデル読み込み
	loader = ObjModelLoader();
	gModelManager["biru2"] = loader.Load(
		"assets/biru2.obj", L"assets/コンクリート2.jpg");

	//空モデル読み込み
	loader = ObjModelLoader();
	gModelManager["sora"] = loader.Load(
		"assets/sora.obj", L"assets/ステンレス.jpg");

	//檻を持つ鳥モデル読み込み
	loader = ObjModelLoader();
	gModelManager["oritori"] = loader.Load(
		"assets/oritori.obj", L"assets/ステンレス.jpg");

	//ディスクモデル読み込み
	loader = ObjModelLoader();
	gModelManager["disk"] = loader.Load(
		"assets/disk.obj", L"assets/ステンレス.jpg");

	//敵モデル読み込み
	loader = ObjModelLoader();
	gModelManager["teki"] = loader.Load(
		"assets/block.obj", L"assets/ステンレス.jpg"
	);

	////草モデル読み込み
	//loader = ObjModelLoader();
	//gModelManager["disk"] = loader.Load(
	//	"assets/kusa.obj", L"assets/yukijimen.png");

	// 鳥用Modelオブジェクト生成
	gptori = new NormalObject();
	Model* pGunModel = gptori->GetModel();
	pGunModel->SetModelData(gModelManager["gun"]);
	pGunModel->SetScale(0.3f);
	pGunModel->mPos.x = TORIX;
	pGunModel->mPos.y = TORIY;
	pGunModel->mPos.z = TORIZ;
	pGunModel->mRotate.y = TORIROTEY;
	pGunModel->mCamera = gpCamera;

	//当たり判定に必要
	HitSphere* pHit = gptori->GetHit();
	pHit->SetHankei(0.8f);// 当たり判定の半径を設定
	pHit->SetHigh(0.8f);
	pHit->SetWidth(0.9f);

	// 地面モデル読み込み
	loader = ObjModelLoader();
	gModelManager["ground1"] = loader.Load(
		"assets/ground1.obj", L"assets/yukijimen.png"
	);

	// 地面生成
	for (int i = 0; i < MAX_GROUND; i++)
	{
		for (int j = 0; j < MAX_GROUND; j++)
		{
			gpGround[i][j] = new NormalObject();
			Model* pGroundModel = gpGround[i][j]->GetModel();
			pGroundModel->SetModelData(gModelManager["ground1"]);
			pGroundModel->SetScale(2.0f);
			pGroundModel->mPos.x = -20.0f + 4.0f*j;
			pGroundModel->mPos.z = -10.0f + 4.0f*i;
			pGroundModel->mPos.y = -2.0f;
			pGroundModel->mCamera = gpCamera;
			gObjectList.emplace_back(gpGround[i][j]);
		}
	}

	// 弾モデル読み込み
	loader = ObjModelLoader();
	gModelManager["shot"] = loader.Load(
		"assets/billboard.obj", L"assets/effect000.jpg"
	);

	

	// 弾用オブジェクト生成
	gpShot = new BillboardObject();
	Model* pShotModel = gpShot->GetModel();
	pShotModel->SetModelData(gModelManager["shot"]);
	pShotModel->SetScale(0.2f);
	pShotModel->mPos.y = 0.2f;
	pShotModel->mPos.z = 1.0f;
	pShotModel->mCamera = gpCamera;

	// 2Dキャラ用ポリゴン生成
	gModelManager["2Dchar"] =
		CreateSquarePolygon(1.0f, 1.2f,0.0f,0.0f, 0.33f, 0.25f,
			L"assets/char01.png");


	// 2D雪用ポリゴン生成
	gModelManager["2Dyuki"] =
		CreateSquarePolygon(1.0f, 1.0f,0.0f,0.0f, 1.0f, 1.0f,
			L"assets/yuki.png");

	// 2D雪用オブジェクト生成
	for (int len = 0; len < YUKISUU; len++)
	{
		gpyuki[len] = new BillboardObject();
		Model* pyukiModel = gpyuki[len]->GetModel();
		pyukiModel->SetModelData(gModelManager["2Dyuki"]);
		pyukiModel->SetScale(0.3f);
		pyukiModel->mPos.y = 10.0f;
		pyukiModel->mPos.z = rand()%YUKIHANI;
		pyukiModel->mPos.x = rand()%YUKIHANI;
		pyukiModel->mCamera = gpCamera;
		gObjectList.emplace_back(gpyuki[len]);

	}



	for (int len = 0; len < CHARASUU; len++)
	{
		// 2Dキャラ用オブジェクト生成
		gp2Dchar[len] = new BillboardObject();
		Model* p2DModel = gp2Dchar[len]->GetModel();
		p2DModel->SetModelData(gModelManager["2Dchar"]);
		p2DModel->SetScale(1.0f);
		p2DModel->mPos.y = 0.6f;
		p2DModel->mPos.z = 5.0f;
		p2DModel->mPos.x = 5.0+len*3;
		p2DModel->mCamera = gpCamera;
		pHit = gp2Dchar[len]->GetHit();
		pHit->SetHankei(0.8f);// 当たり球の半径を設定
		gObjectList.emplace_back(gp2Dchar[len]);
	}

	// 敵用Modelオブジェクト生成
	for (int len = 0; len < TEKISUU; len++)
	{
		gpteki[len] = new NormalObject();
		Model* pModel = gpteki[len]->GetModel();
		pModel->SetModelData(gModelManager["teki"]);
		pModel->SetScale(2.5f);
		pModel->mPos.y = 0.4f;
		pModel->mPos.z = 10.0f;
		pModel->mPos.x = 10.0f;
		pModel->mRotate.y = 90.0f;
		pModel->mCamera = gpCamera;
		pHit = gpteki[len]->GetHit();	//当たり判定に必要
		pHit->SetHankei(0.8f);// 当たり判定の半径を設定
		pHit->SetHigh(0.5f);
		pHit->SetWidth(0.5f);
		gObjectList.emplace_back(gpteki[len]);
	}


	// 檻用Modelオブジェクト生成
	gpori = new NormalObject();
	Model* pOriModel = gpori->GetModel();
	pOriModel->SetModelData(gModelManager["ori"]);
	pOriModel->SetScale(0.5f);
	pOriModel->mPos.y = 0.4f;
	pOriModel->mPos.z = 10.0f;
	pOriModel->mPos.x = 10.0f;
	pOriModel->mRotate.y = 90.0f;
	pOriModel->mCamera = gpCamera;
	pHit = gpori->GetHit();	//当たり判定に必要
	pHit->SetHankei(0.8f);// 当たり判定の半径を設定
	pHit->SetHigh(0.5f);
	pHit->SetWidth(0.5f);

	// ディスク用Modelオブジェクト生成
	for (int len = 0; len < DISKSUU; len++)
	{
		gpdisk[len] = new NormalObject();
		Model* pDiModel = gpdisk[len]->GetModel();
		pDiModel->SetModelData(gModelManager["disk"]);
		pDiModel->SetScale(0.5f);
		pDiModel->mPos.y = rand() % TAKASA;
		pDiModel->mPos.z = rand() % YUKIHANI;
		pDiModel->mPos.x = rand() % YUKIHANI;
		pDiModel->mRotate.y = 90.0f;
		pDiModel->mCamera = gpCamera;
		pHit = gpdisk[len]->GetHit();	//当たり判定に必要
		pHit->SetHankei(0.8f);// 当たり判定の半径を設定
		pHit->SetHigh(0.5f);    //当たり判定の高さを設定
		pHit->SetWidth(0.5f);   //当たり判定の広さを設定
		gObjectList.emplace_back(gpdisk[len]);
	}

	//for (int len = 0; len < KUSASUU; len++)
	//{
	//	// ディスク用Modelオブジェクト生成
	//	gpkusa = new NormalObject();
	//	Model* pKusaModel = gpkusa->GetModel();
	//	pKusaModel->SetModelData(gModelManager["disk"]);
	//	pKusaModel->SetScale(0.5f);
	//	pKusaModel->mPos.z = rand()%YUKIHANI;
	//	pKusaModel->mPos.x = rand()%YUKIHANI;
	//	pKusaModel->mRotate.y = 90.0f;
	//	pKusaModel->mCamera = gpCamera;
	//	gObjectList.emplace_back(gpkusa);
	//
	//}

	// 空用Modelオブジェクト生成
	gpsora = new NormalObject();
	Model* pSoraModel = gpsora->GetModel();
	pSoraModel->SetModelData(gModelManager["sora"]);
	pSoraModel->SetScale(100.0f);
	pSoraModel->mPos.y = 0.4f;
	pSoraModel->mPos.z = 10.0f;
	pSoraModel->mPos.x = 10.0f;
	pSoraModel->mRotate.y = 90.0f;
	pSoraModel->mCamera = gpCamera;

	
	gObjectList.emplace_back(gpsora);



	gObjectList.emplace_back(gpori);

	gObjectList.emplace_back(gptori);
	

	// ビル用オブジェクト生成

	{
		int birunum = 0;
		for (int len = 0; len < MAPX; len++)
		{
			for (int sen = 0; sen < MAPY; sen++)
			{
				if (map3[len][sen] != 0)
				{
					gpbiru[birunum] = new NormalObject();
					Model* pbiruModel = gpbiru[birunum]->GetModel();
					pbiruModel->SetModelData(gModelManager["biru"]);
					pbiruModel->SetScale(1.5f);
					pbiruModel->mPos.x = 0.8 + len * 8.0f;
					pbiruModel->mPos.z = 1.0 + sen * 8.0f;
					pbiruModel->mRotate.y = 90;
					pbiruModel->mCamera = gpCamera;
 					pHit = gpbiru[birunum]->GetHit();	//当たり判定に必要
					pHit->SetHankei(5.0f);// 当たり判定の半径を設定
					pHit->SetHigh(7.0f);
					pHit->SetWidth(0.6f);
					gObjectList.emplace_back(gpbiru[birunum]);

					birunum++;
				}
			}
		}
	}
	

	//gpbiru[0] = new NormalObject();
	//Model* pbiruModel = gpbiru[0]->GetModel();
	//pbiruModel->SetModelData(gModelManager["biru"]);
	//pbiruModel->SetScale(1.5f);
	//pbiruModel->mPos.x = 5.8f;
	//pbiruModel->mPos.z = 5.0f;
	//pbiruModel->mRotate.y = rand() % 360;
	//pbiruModel->mCamera = gpCamera;
	//pHit = gpbiru[0]->GetHit();	//当たり判定に必要
	//pHit->SetHankei(5.0f);// 当たり判定の半径を設定
	//pHit->SetHigh(7.0f);
	//pHit->SetWidth(0.6f);
	//gObjectList.emplace_back(gpbiru[0]);

	//ビル2用オブジェクト作成
	for (int i = 0; i < BIRU2SUU; i++)
	{
		gpbiru2[i] = new NormalObject();
		Model* pbiru2Model = gpbiru2[i]->GetModel();
		pbiru2Model->SetModelData(gModelManager["biru2"]);
		pbiru2Model->mCamera = gpCamera;
		pHit = gpbiru2[i]->GetHit();	//当たり判定に必要
		pHit->SetHankei(5.0f);// 当たり判定の半径を設定
		pHit->SetHigh(5.0f);
		pHit->SetWidth(0.8f);
		if (i < 3)
		{
			pbiru2Model->SetScale(0.5f);
			pbiru2Model->mPos.y = i * 4.2f;
			pbiru2Model->mPos.z = 20.0f;
			pbiru2Model->mPos.x = 0.0;
			pbiru2Model->mRotate.y = 90.0f;
		}
		if(i == 3)
		{
			pbiru2Model->SetScale(0.5f);
			pbiru2Model->mPos.y = 0.0f;
			pbiru2Model->mPos.z = 25.0f;
			pbiru2Model->mPos.x = 0.0;
			pbiru2Model->mRotate.y = 90.0f;
		}
		if (i == 4)
		{
			pbiru2Model->SetScale(0.5f);
			pbiru2Model->mPos.y = 4.2f;
			pbiru2Model->mPos.z = 25.0f;
			pbiru2Model->mPos.x = 0.0;
			pbiru2Model->mRotate.y = 90.0f;
		}

		gObjectList.emplace_back(gpbiru2[i]);

	}


	//// コテージ用オブジェクト生成
	//for (int i = 0; i < 5; i++)
	//{
	//	gpCottage = new NormalObject();
	//	Model* pCottageModel = gpCottage->GetModel();
	//	pCottageModel->SetModelData(gModelManager["cottage"]); // 3Dデータをセットする
	//	pCottageModel->SetScale(0.002f);
	//	pCottageModel->mPos.x = -30.0f + i * 6.5f;
	//	pCottageModel->mPos.z = 5.0f;
	//	pCottageModel->mPos.y = 0.0f;
	//	gObjectList.emplace_back(gpCottage);
	//}

	//爆発クラス
	gModelManager["explosion"] = CreateSquarePolygon(1.0f, 1.0f,0.0f,0.0f, 0.25f, 0.25f, L"assets/explosion.png");
	GameObject* tmp = new Explosion(4,4);
   
	Model* pModel = tmp->GetModel();
	pModel->SetModelData(gModelManager["explosion"]);
	gObjectList.emplace_back(tmp);


	//爆発クラス
	gModelManager["baku"] = CreateSquarePolygon(1.0f, 1.0f, 0.0f, 0.0f, 0.1f, 1.0f, L"assets/baku.png");

	tmp = new Explosion(8, 1);
	pModel = tmp->GetModel();
	pModel->SetModelData(gModelManager["baku"]);
	gObjectList.emplace_back(tmp);



	//タイトル画像を生成
	gModelManager["title"] = CreateSquarePolygon(2.0f, 2.0f,0.0f,0.0f, 1.0f, 1.0f, L"assets/タイトル.png");
    title = new NormalObject();
	pModel = title->GetModel();
	pModel->SetModelData(gModelManager["title"]);
	pModel->Set2dRender(false); // 2Dモードで表示する設定
	pModel->SetDiffuse(XMFLOAT4(1, 0, 0, 1.0f)); //マテリアル色設定
	gObjectList.emplace_back(title);


	//数字画像を生成
	for (int len = 0; len < SUJISUU; len++)
	{
		for (int sen = 0; sen < SUJIHYOUJI; sen++)
		{
			gModelManager["suji"] = CreateSquarePolygon(0.1f, 0.1f, SUJIUV*len, 0.0f, 0.07 + (SUJIUV*len), 1.0f, L"assets/suji.png");
			suji[len][sen] = new NormalObject();
			pModel = suji[len][sen]->GetModel();
			pModel->SetModelData(gModelManager["suji"]);
			pModel->Set2dRender(false); // 2Dモードで表示する設定
			pModel->SetDiffuse(XMFLOAT4(1, 1, 1, 1.0f)); //マテリアル色設定
			pModel->mPos.y = 0.8f;
			pModel->mPos.x = 0.9f;
			gObjectList.emplace_back(suji[len][sen]);
		}
	}

	//時計画像を生成
	gModelManager["watch"] = CreateSquarePolygon(0.3f, 0.3f, 0.0f, 0.0f, 1.0f, 1.0f, L"assets/タイム.png");
	watch = new NormalObject();
	pModel = watch->GetModel();
	pModel->SetModelData(gModelManager["watch"]);
	pModel->Set2dRender(false); // 2Dモードで表示する設定
	pModel->SetDiffuse(XMFLOAT4(1, 1, 1, 1.0f)); //マテリアル色設定
	pModel->mPos.y = 0.8f;
	pModel->mPos.x = -0.6f;
	gObjectList.emplace_back(watch);





	//プリーズエンター画像を生成
	gModelManager["enter"] = CreateSquarePolygon(0.3f, 0.3f, 0.0f, 0.0f, 1.0f, 1.0f, L"assets/PressEnter.png");
	plessen = new NormalObject();
	pModel = plessen->GetModel();
	pModel->SetModelData(gModelManager["enter"]);
	pModel->Set2dRender(false); // 2Dモードで表示する設定
	pModel->SetDiffuse(XMFLOAT4(1, 1, 1, 1.0f)); //マテリアル色設定
	pModel->mPos.x = 0.0f;
	pModel->mPos.y = -0.3f;
	gObjectList.emplace_back(plessen);

	//ディスク画像を生成
	gModelManager["aicon"] = CreateSquarePolygon(0.3f, 0.3f, 0.0f, 0.0f, 1.0f, 1.0f, L"assets/ディスク.png");
	aicon = new NormalObject();
	pModel = aicon->GetModel();
	pModel->SetModelData(gModelManager["aicon"]);
	pModel->Set2dRender(false); // 2Dモードで表示する設定
	pModel->SetDiffuse(XMFLOAT4(1, 1, 1, 1.0f)); //マテリアル色設定
	pModel->mPos.x = 0.6f;
	pModel->mPos.y = 0.8f;
	gObjectList.emplace_back(aicon);

	//ゲームオーバー画像を生成
	gModelManager["gameover"] = CreateSquarePolygon(2.0f, 2.0f, 0.0f, 0.0f, 1.0f, 1.0f, L"assets/ゲームオーバー.png");
	gameover = new NormalObject();
	pModel = gameover->GetModel();
	pModel->SetModelData(gModelManager["gameover"]);
	pModel->Set2dRender(false); // 2Dモードで表示する設定
	pModel->SetDiffuse(XMFLOAT4(1, 1, 1, 1.0f)); //マテリアル色設定
	gObjectList.emplace_back(gameover);


	//クリア画像を生成
	gModelManager["clear"] = CreateSquarePolygon(2.0f, 2.0f, 0.0f, 0.0f, 1.0f, 1.0f, L"assets/result.png");
	clear = new NormalObject();
	pModel = clear->GetModel();
	pModel->SetModelData(gModelManager["clear"]);
	pModel->Set2dRender(false); // 2Dモードで表示する設定
	pModel->SetDiffuse(XMFLOAT4(1, 1, 1, 1.0f)); //マテリアル色設定
	gObjectList.emplace_back(clear);

	//チュートリアル画像を生成
	gModelManager["tyuuto"] = CreateSquarePolygon(1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, L"assets/チュートリアル.png");
	tyutori = new NormalObject();
	pModel = tyutori->GetModel();
	pModel->SetModelData(gModelManager["tyuuto"]);
	pModel->Set2dRender(false); // 2Dモードで表示する設定
	pModel->SetDiffuse(XMFLOAT4(1, 1, 1, 1.0f)); //マテリアル色設定
	pModel->mPos.x = 0.5f;

	gObjectList.emplace_back(tyutori);

	//ゲームスタート画像を生成
	gModelManager["start"] = CreateSquarePolygon(1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, L"assets/ゲームスタート.png");
	gamestart = new NormalObject();
	pModel = gamestart->GetModel();
	pModel->SetModelData(gModelManager["start"]);
	pModel->Set2dRender(false); // 2Dモードで表示する設定
	pModel->SetDiffuse(XMFLOAT4(1, 1, 1, 1.0f)); //マテリアル色設定
	pModel->mPos.x = -0.5f;
	
	gObjectList.emplace_back(gamestart);

	//矢印画像を生成
	gModelManager["yajirusi"] = CreateSquarePolygon(0.3f, 0.3f, 0.0f, 0.0f, 1.0f, 1.0f, L"assets/やじるし.png");
	yajirusi = new NormalObject();
	pModel = yajirusi->GetModel();
	pModel->SetModelData(gModelManager["yajirusi"]);
	pModel->Set2dRender(false); // 2Dモードで表示する設定
	pModel->SetDiffuse(XMFLOAT4(1, 1, 1, 1.0f)); //マテリアル色設定
	gObjectList.emplace_back(yajirusi);

	//セレクト画像を生成
	gModelManager["serect"] = CreateSquarePolygon(2.0f, 2.0f, 0.0f, 0.0f, 1.0f, 1.0f, L"assets/serect.png");
	serect = new NormalObject();
	pModel = serect->GetModel();
	pModel->SetModelData(gModelManager["serect"]);
	pModel->Set2dRender(false); // 2Dモードで表示する設定
	pModel->SetDiffuse(XMFLOAT4(1, 1, 1, 1.0f)); //マテリアル色設定
	gObjectList.emplace_back(serect);

	//CSVファイルからMAPデータを読み込む
	Csv csv{ "map01.csv" };	//csvファイル名指定して"Csv"クラス変数を作成。
	int data_size = csv.read();	//CSVファイルを読み込む。戻り値は読み込んだデータ数（intデータの数）
	if (data_size < 0) {
		//read()の戻り値が０やマイナス値ならエラー。

	}


	// カメラの追従ターゲットを指定
	//((BackCamera*)gpCamera)->SetTarget(gptori);  // Cスタイルキャスト
	dynamic_cast<BackCamera*>(gpCamera)->SetTarget(gptori); // C++キャスト
}



void Game_Draw()
{
	// DIRECT3D構造体にアクセスする
	DIRECT3D* d3d = Direct3D_Get();

	// 画面クリア（指定色で塗りつぶし）
	// 塗りつぶし色の指定（小数：0.0f～1.0f）
	float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; //red,green,blue,alpha

	d3d->context->ClearRenderTargetView(d3d->renderTarget, clearColor);

	// Zバッファ、ステンシルバッファクリア
	d3d->context->ClearDepthStencilView(
		d3d->depthStencilView,			// デプスステンシルビュー
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
		1.0f,			// Ｚバッファを1.0でクリアする(0.0f～1.0f)
		0);				// ステンシルバッファを0でクリアする

	// ↓　自前の描画処理をここに書く *******

	// ゲームオブジェクトを描画
	d3d->context->OMSetBlendState(d3d->blendAlpha, NULL, 0xffffffff);// アルファブレンド

	vector_DrawAll(gObjectList);

	d3d->context->OMSetBlendState(d3d->blendAdd, NULL, 0xffffffff);// 加算合成
	// 弾管理配列の中身を全てDrawする
	vector_DrawAll(gShotManager);

	vector_DrawAll(gEffectManager);

	gpActiveScene->Draw();

	// ダブルバッファの切り替え
	d3d->swapChain->Present(0, 0);
}

void Game_Update()
{
	// デルタタイムが想定外の値になった場合の処理
	if (gDeltaTime >= 100)
	{
		gDeltaTime = 0;
	}
	if (gDeltaTime <= 0)
	{
		gDeltaTime = 1;
	}



	//シーン遷移
	switch (gNowScene)
	{
	case TITLE:
		TitleUpdate();
		break;

	case STAGE:
		StageUpdate();
		break;
	case RESULT:
		ResultUpdate();
		break;
	case SERECT:
		SerectUpdate();
		break;
	case TYUTORIAL:
		TyutoUpdate();
		break;
	}



	// カメラ移動変数
	static float angle = 0.5f; // 回転角度
	static float zoom = 3.0f;  // ズーム

	// ①カメラの位置をキー操作で移動する
	if (Input_GetKeyDown(VK_RIGHT))
	{
		angle += 0.5;
	}
	if (Input_GetKeyDown(VK_LEFT))
	{
		angle -= 0.5f;
	}
	// ズーム操作
	if (Input_GetKeyDown(VK_UP))
		zoom -= 0.01f * gDeltaTime;
	if (Input_GetKeyDown(VK_DOWN))
		zoom += 0.01f * gDeltaTime;

	// ②カメラの注視点を中心にカメラを回転する

	// カメラ位置X　＝　sinf(角度ラジアン)
	// カメラ位置Z　＝　cosf(角度ラジアン)
	// 原点を中心に半径1.0fの円周上の点を求める
	Model* ptoriModel = gptori->GetModel();
	float radian = XMConvertToRadians(angle);
	//gpCamera->mEye.x =
	//	sinf(radian) * zoom + pCottageModel->mPos.x;
	//gpCamera->mEye.z =
	//	cosf(radian) * zoom + pCottageModel->mPos.z;
	//gpCamera->mEye.y = 2.0f;
	gpCamera->mEye.x =
		sinf(radian) * zoom + ptoriModel->mPos.x;
	gpCamera->mEye.z =
		cosf(radian) * zoom + ptoriModel->mPos.z;
	gpCamera->mEye.y = 2.0f;
	// カメラ注視点をコテージの位置にする
	//gpCamera->SetFocus(pCottageModel->mPos);
	gpCamera->SetFocus(ptoriModel->mPos);

	

	vector_UpdateAll(gObjectList);

	// 弾管理配列の中身を全てUpdateする
	vector_UpdateAll(gShotManager);

	// 弾の回収処理
	for (int i = 0; i < gShotManager.size(); i++)
	{
		// (a)カメラの位置
		XMFLOAT3 cameraPos = gpCamera->mEye;
		// (b)弾の位置
		XMFLOAT3 shotPos = gShotManager[i]->GetModel()->mPos;
		// (b)→(a)ベクトル
		XMVECTOR abVector =
			XMLoadFloat3(&cameraPos) - XMLoadFloat3(&shotPos);
		// (b)→(a)ベクトルの長さを計算
		XMVECTOR abVecLength = XMVector3Length(abVector);
		float abLength = XMVectorGetX(abVecLength);
		// abLengthが○○以上なら弾を回収する
		if (abLength >= 50.0f)
		{
			// erase関数だけでは弾のdeleteは行われない
			delete gShotManager[i];
			// 弾管理配列から弾を削除
			gShotManager.erase(gShotManager.begin() + i);
		}
	}

	
	vector_UpdateAll(gEffectManager);

	// 再生が終わったエフェクトを消す
	for (int i = 0; i < gEffectManager.size(); i++)
	{
		Explosion* e = dynamic_cast<Explosion*>(gEffectManager[i]);
		if (e->IsFinished())
		{
			delete gEffectManager[i];
			// 弾管理配列から弾を削除
			gEffectManager.erase(gEffectManager.begin() + i);
			i--;
		}
	}

	// カメラ更新（ビュー変換行列計算）
	gpCamera->Update();
}

void Game_Release()
{
	vector_DeleteAll(gObjectList);

	// 弾管理配列の中身を全てdeleteする
	vector_DeleteAll(gShotManager);	

	vector_DeleteAll(gEffectManager);

	COM_SAFE_RELEASE(gpConstBuffer);

	// モデルマネージャーが持つ全モデルを解放
	for (auto i = gModelManager.begin();//連想配列の先頭情報
		i != gModelManager.end();//連想配列の最後尾情報
		i++)
	{
		// first … 添え字
		// second … 要素そのもの
		COM_SAFE_RELEASE(i->second.mSRV);//テクスチャ
		COM_SAFE_RELEASE(i->second.mVertexBuffer);//頂点バッファ
	}
	// 連想配列の全要素を削除する（要素数０にする）
	gModelManager.clear();
}

void TitleUpdate()
{

	if (gmaeScene == RESULT)
	{
		gmaeScene = TITLE;
	}


	Set(clear, false, 1, 1, 1, 1.0f);
	Set(gameover, false, 1, 1, 1, 1.0f);


	//タイトルロゴ表示
	Set(title,true,1,1,1,1.0f);

	static float toumei = 0;

	//プリーズエンター表示
	Set(plessen, true, 1, 1, 1, toumei);

	//透明度を変更
	toumei += 0.001;
	if(toumei >= 1.0)
	{
		toumei = 0.0;
	}

	//スペースキーを押すとセレクト画面に遷移
	if (Input_GetKeyDown(VK_SPACE))
	{
		gNowScene = SERECT;
	}

}

void StageUpdate()
{
	static int point = 0;                  //点数

	static int torihp = TORIHP;            //鳥HP

	static int limit = TIMELIMIT * 60;     //タイムリミット

	static int mutekitime = MUTEKI*60;    //無敵時間

	static bool atari = false;      //無敵になっているか

	static int starttime = STARTCOUNT*60;


	starttime--;


	Model* toriModel = gptori->GetModel();

	if (atari == true)
	{
		mutekitime--;
		toriModel->SetDiffuse(XMFLOAT4(1, 0, 0, 1.0f));
		if (mutekitime == 0)
		{
			mutekitime = MUTEKI * 60;
			atari = false;
		}
	}
	else
	{
		toriModel->SetDiffuse(XMFLOAT4(1, 1, 1, 1.0f));
	}


	//初期化
	if ((gmaeScene == SERECT)||(gmaeScene == TYUTORIAL))
	{
		Set(tyutori, false, 1, 1, 1, 1.0f);
		Set(gamestart, false , 1, 1, 1, 1.0f);
		Set(yajirusi, false , 1, 1, 1, 1.0f);
		Set(serect, false, 1, 1, 1, 1.0f);
		Set(plessen, false, 1, 1, 1, 1.0f);
		Set(clear,false,1,1,1,1.0f);

		point = 0;
		torihp = TORIHP;
		limit = TIMELIMIT * 60;
		gresult = NONE2;
		Model* toriModel = gptori->GetModel();
		toriModel->mPos.x = TORIX;
		toriModel->mPos.y = TORIY;
		toriModel->mPos.z = TORIZ;
		toriModel->mRotate.y = TORIROTEY;
		toriModel->mRotate.z = TORIROTEZ;
		mutekitime = MUTEKI * 60;    //無敵時間
		atari = false;
		gptori->mSpeed = 0; //鳥の速さ
		starttime = STARTCOUNT * 60;
		gmaeScene = STAGE;

	}
	
	////スコア表示//////////////////////////
	//初期化
	for (int len = 0; len < SUJISUU; len++)
	{
		for (int sen = 0; sen < SUJIHYOUJI; sen++)
		{
			Set(suji[len][sen], false, 1, 1, 1, 1.0f);
		}
	}

	int one = 0;  //一の位
	int ten = 0;  //十の位

	ten = point / 10;
	one = point % 10;

	//十の位処理
	Model* psujiModel = suji[ten][0]->GetModel();
	psujiModel->mPos.y = 0.8f;
	psujiModel->mPos.x = 0.8f;
	Set(suji[ten][0], true, 1, 1, 1, 1.0f);
	
	//一の位処理
	psujiModel = suji[one][1]->GetModel();
	psujiModel->mPos.y = 0.8f;
	psujiModel->mPos.x = 0.9f;
	Set(suji[one][0], true, 1, 1, 1, 1.0f);
	//////////////////////////////////////////////////////
	
	

	Set(aicon, true, 1, 1, 1, 1.0f);

	Set(watch, true, 1, 1, 1, 1.0f);


	////タイムリミット表示////////////////////

	//カウントダウンが終わるまで動かない
	if (!((starttime / 60) >= 0))
	{
		limit -= 1;
	}

	int hundred = 0; //百の位

	hundred = (limit / 60) / 100;
	ten = ((limit/60)%100) / 10;
	one = (limit/60) % 10;

	//百の位処理
	psujiModel = suji[hundred][2]->GetModel();
	psujiModel->mPos.y = 0.8f;
	psujiModel->mPos.x = -0.5f;
	Set(suji[hundred][2], true, 1, 1, 1, 1.0f);


	//十の位処理
	psujiModel = suji[ten][3]->GetModel();
	psujiModel->mPos.y = 0.8f;
	psujiModel->mPos.x = -0.4f;
	Set(suji[ten][3], true, 1, 1, 1, 1.0f);

	//一の位処理
	psujiModel = suji[one][4]->GetModel();
	psujiModel->mPos.y = 0.8f;
	psujiModel->mPos.x = -0.3f;
	Set(suji[one][4], true, 1, 1, 1, 1.0f);
    //////////////////////////////////////


	//カウントダウン/////////

	if ((starttime/60) >= 0)
	{
		psujiModel = suji[starttime / 60][5]->GetModel();
		psujiModel->mPos.y = 0.0f;
		psujiModel->mPos.x = 0.0f;
		Set(suji[starttime / 60][5], true, 1, 1, 1, 1.0f);
	}
	/////////////////////////////


	//雪を降らせる処理
	for (int len = 0; len < YUKISUU; len++)
	{
		Model* pyuki = gpyuki[len]->GetModel();
		pyuki->mPos.y -= YUKISPEED;
		if (pyuki->mPos.y <= 0)
	
		{
			pyuki->mPos.x = rand() % YUKIHANI;
			pyuki->mPos.y = YUKITAKASA;
			pyuki->mPos.y = rand() % YUKIHANI;
		}
	}

	// キャラクター移動
	// キャラクターが向いている方向に前進する
	// 向き変更＝ADキー　前進＝Wキー
	// 「前向きベクトル」を計算する
	Model* ptori = gptori->GetModel();

	static float tilt = 0;
	// 鳥の方向転換
	if (Input_GetKeyDown('W'))
	{
		if (ptori->mRotate.z <= 90)
		{
			ptori->mRotate.z += CHANGESPEED;
			tilt += 1;
		}
	}
	else if (Input_GetKeyDown('S'))
	{
		if (ptori->mRotate.z >= -90)
		{
			ptori->mRotate.z -= CHANGESPEED;
			tilt -= 1;
		}
	}
	else if (Input_GetKeyDown('A'))
	{
		ptori->mRotate.y -= CHANGESPEED;
		if (ptori->mRotate.x > -90)
			ptori->mRotate.x -= CHANGESPEED;
	}
	else if (Input_GetKeyDown('D'))
	{
		ptori->mRotate.y += CHANGESPEED;
		if (ptori->mRotate.x < 90)
			ptori->mRotate.x += CHANGESPEED;
	}
	else
	{
		if (ptori->mRotate.x < 0)
			ptori->mRotate.x += CHANGESPEED;
		if (ptori->mRotate.x > 0)
			ptori->mRotate.x -= CHANGESPEED;
	}


	//カウントダウンが終わるまで動かない
	if (!((starttime / 60) >= 0))
	{
		//鳥の速さ
		gptori->mSpeed = SPEED;
	}

	//傾き計算
	XMFLOAT3 forwardVec = gptori->GetForwardVector();
	if (ptori->mRotate.z < -10)
	{
		//ptori->mPos.x = ptori->mPos.x + forwardVec.x * 0.001f;
		
		ptori->mPos.y += 0.009f;
		//ptori->mPos.z = ptori->mPos.z + forwardVec.z * 0.001f;
		

		if ((ptori->mRotate.z > -90) && (ptori->mRotate.z < -80))
		{
			ptori->mPos.y += 0.032f;
		}
		
		if (ptori->mRotate.z <= -90)
		{
			ptori->mPos.y += 0.05f;
		}
	}
	if (ptori->mRotate.z > 10)
	{
		//ptori->mPos.x = ptori->mPos.x + forwardVec.x * 0.001f;
		ptori->mPos.y -= 0.009f;
		//ptori->mPos.z = ptori->mPos.z + forwardVec.z * 0.001f;
		if ((ptori->mRotate.z < 90) && (ptori->mRotate.z > 80))
		{
			ptori->mPos.y -= 0.032f;
		}

		if (ptori->mRotate.z >= 90)
		{
			ptori->mPos.y -= 0.05f;
		}
	}

	// 弾の発射
	//f (Input_GetKeyDown(VK_LBUTTON))
	//
	//	// 弾オブジェクト生成
	//	GameObject* pShot = new BillboardObject();
	//	Model* pShotModel = pShot->GetModel();
	//	pShotModel->SetModelData(gModelManager["shot"]);
	//	pShotModel->SetScale(0.2f);
	//	pShot->GetHit()->SetHankei(0.19f);
	//	
	//	// 発射地点に移動させる
	//	XMFLOAT3 forwardVec = gptori->GetForwardVector();
	//
	//	pShotModel->mPos.x =
	//		pGunModel->mPos.x + forwardVec.x * 0.8f;
	//	pShotModel->mPos.y = pGunModel->mPos.y + 0.2f;
	//	pShotModel->mPos.z =
	//		pGunModel->mPos.z + forwardVec.z * 0.8f;
	//	// 弾に速度を設定する
	//	pShot->mSpeed = 0.01f;
	//	// 弾が飛ぶ方向を設定
	//	pShotModel->mRotate.y = pGunModel->mRotate.y;
	//
	//	// 弾管理配列に追加する
	//	gShotManager.emplace_back(pShot);
	//

	HitSphere* ptoriHit = gptori->GetHit();
	
	// 弾とNPC当たり判定
	for (int len = 0; len < CHARASUU; len++)
	{

		if (ptoriHit->IsHit(gp2Dchar[len]->GetHit()))
		{

			// emitter
			int num = rand() % 4 + 3;
			for (int j = 0; j < num; j++)
			{
				GameObject* tmp = new Explosion(4,4);
				Model* pModel = tmp->GetModel();
				pModel->SetModelData(gModelManager["explosion"]);
				pModel->mPos = gp2Dchar[len]->GetModel()->mPos;
				pModel->mPos.x += static_cast<float>(rand() % 100 - 50) / 100.0f;
				pModel->mPos.y += static_cast<float>(rand() % 100 - 50) / 100.0f;
				pModel->mPos.z += static_cast<float>(rand() % 100 - 50) / 100.0f;
				//tmp->mSpeed = static_cast<float>(rand() % 100) / 100000.0f;
				gEffectManager.emplace_back(tmp);
			}
		}
	}


	if (atari == false)
	{
		for (int len = 0; len < BIRUSUU; len++)
		{
			//ビルとの当たり判定
			if (ptoriHit->SquareHit(gpbiru[len]->GetHit()))
			{
				atari = true;
				torihp--;
				// emitter
				int num = rand() % 4 + 3;
				for (int j = 0; j < num; j++)
				{
					GameObject* tmp = new Explosion(4, 4);
					Model* pModel = tmp->GetModel();
					pModel->SetModelData(gModelManager["explosion"]);
					pModel->mPos = gptori->GetModel()->mPos;
					pModel->mPos.x += static_cast<float>(rand() % 100 - 50) / 100.0f;
					pModel->mPos.y += static_cast<float>(rand() % 100 - 50) / 100.0f;
					pModel->mPos.z += static_cast<float>(rand() % 100 - 50) / 100.0f;
					//tmp->mSpeed = static_cast<float>(rand() % 100) / 100000.0f;
					gEffectManager.emplace_back(tmp);
				}
			}
		}
	}

	//ディスクとビルの当たり判定
	for (int len = 0; len < DISKSUU; len++)
	{
		for (int sen = 0; sen < BIRUSUU; sen++)
		{
			HitSphere* pdiskHit = gpdisk[len]->GetHit();
			Model* pDiModel = gpdisk[len]->GetModel();
			//ビルとの当たり判定
			if (pdiskHit->IsHit(gpbiru[sen]->GetHit()))
			{
				//ビルと重なっている場合重ならなくなるまで座標を変更
				do {
					pDiModel->mPos.y = rand() % TAKASA;
					pDiModel->mPos.z = rand() % YUKIHANI;
					pDiModel->mPos.x = rand() % YUKIHANI;

				} while (pdiskHit->IsHit(gpbiru[sen]->GetHit()));
			}
		
		}
	}


	//ディスクとの当たり判定
	for (int len = 0; len < DISKSUU; len++)
	{
		if (ptoriHit->IsHit(gpdisk[len]->GetHit()))
		{
			point++;
			Model* pDiModel = gpdisk[len]->GetModel();
			int num = rand() % 4 + 3;
			for (int j = 0; j < num; j++)
			{
				GameObject* tmp = new Explosion(4,4);
				Model* pModel = tmp->GetModel();
				pModel->SetModelData(gModelManager["explosion"]);
				pModel->mPos = gptori->GetModel()->mPos;
				pModel->mPos.x += static_cast<float>(rand() % 100 - 50) / 100.0f;
				pModel->mPos.y += static_cast<float>(rand() % 100 - 50) / 100.0f;
				pModel->mPos.z += static_cast<float>(rand() % 100 - 50) / 100.0f;
				//tmp->mSpeed = static_cast<float>(rand() % 100) / 100000.0f;
				gEffectManager.emplace_back(tmp);

				if (j == num - 1)
				{
					pDiModel->mPos.y = rand() % TAKASA;
					pDiModel->mPos.z = rand() % YUKIHANI;
					pDiModel->mPos.x = rand() % YUKIHANI;
				}
			}
		}
	}

	if (atari == false)
	{
		//地面より下にいった場合
		if (ptori->mPos.y <= 0)
		{
			atari = true;
			torihp--;

			GameObject* tmp = new Explosion(4, 4);
			Model* pModel = tmp->GetModel();
			pModel->SetModelData(gModelManager["explosion"]);
			pModel->mPos = gptori->GetModel()->mPos;
			pModel->mPos.x += static_cast<float>(rand() % 100 - 50) / 100.0f;
			pModel->mPos.y += static_cast<float>(rand() % 100 - 50) / 100.0f;
			pModel->mPos.z += static_cast<float>(rand() % 100 - 50) / 100.0f;
			//tmp->mSpeed = static_cast<float>(rand() % 100) / 100000.0f;
			gEffectManager.emplace_back(tmp);
		}
	}

	
	static int birucount = 0;
	
	//カウントダウンが終わるまで動かない
	if (!((starttime / 60) >= 0))
	{
		for (int len = 0; len < BIRUSUU/20; len++)
		{
			Model* pbiru = gpbiru[len]->GetModel();
			if (birucount % 2 == 0)
			{
				pbiru->mPos.y -= 0.007;
			}
			
			for (int j = 0; j < 10; j++)
			{
				GameObject* tmp = new Explosion(4, 4);
				Model* pModel = tmp->GetModel();
				pModel->SetModelData(gModelManager["explosion"]);
				pModel->mPos = gpbiru[0]->GetModel()->mPos;
				
				pModel->mPos.x += static_cast<float>(rand() % 100 - 50) / 10.0f;
				if (pModel->mPos.y > -5)
				{
					pModel->mPos.y += static_cast<float>(rand() % 100 - 50) / 10.0f;
				}
				else
				{
					pModel->mPos.y += 2.5; 
					pModel->mPos.y += static_cast<float>(rand() % 100 - 50) / 10.0f;
				}
				pModel->mPos.z += static_cast<float>(rand() % 100 - 50) / 10.0f;

				//tmp->mSpeed = static_cast<float>(rand() % 100) / 100000.0f;
				gEffectManager.emplace_back(tmp);
			}
			

		}
	}

	

	birucount++;

	
	//for (int len = 0; len < TEKISUU; len++)
	//{
	//	for (int j = 0; j < 20; j++)
	//	{
	//		GameObject* tmp = new Explosion(4, 4);
	//		Model* pModel = tmp->GetModel();
	//		pModel->SetModelData(gModelManager["suji"]);
	//		pModel->mPos = gpteki[len]->GetModel()->mPos;
	//		pModel->mPos.x += static_cast<float>(rand() % 100 - 50)/10.0f;
	//		pModel->mPos.y += static_cast<float>(rand() % 100 - 50)/10.0f;
	//		pModel->mPos.z += static_cast<float>(rand() % 100 - 50)/10.0f;
	//		//tmp->mSpeed = static_cast<float>(rand() % 100) / 100000.0f;
	//		gEffectManager.emplace_back(tmp);
	//	}
	//}

	for (int len = 0; len < TEKISUU; len++)
	{
		Model* pteki = gpteki[len]->GetModel();
		pteki->mPos.x -= 0.01f;

	}
		

	//時間がたつとresultに遷移
	if (limit == 0)
	{
		gNowScene = RESULT;
		gresult = CLEAR;
		tensuu = point;
	}

	//ゲームオーバー
	if (torihp == 0)
	{
		gNowScene = RESULT;
		gresult = GAMEOVER;
	}


	
}

void ResultUpdate()
{
	if (gmaeScene == STAGE)
	{
		gmaeScene = RESULT;
	}
	//初期化
	for (int len = 0; len < SUJISUU; len++)
	{
		for (int sen = 0; sen < SUJIHYOUJI; sen++)
		{
			Set(suji[len][sen], false, 1, 1, 1, 1.0f);
		}
	}
	Set(aicon, false, 1, 1, 1, 1.0f);

	Set(watch, false, 1, 1, 1, 1.0f);


	if (gresult == CLEAR)
	{
		Set(clear, true, 1, 1, 1, 1.0f);

		//点数

		int one = 0;  //一の位
		int ten = 0;  //十の位

		ten = tensuu / 10;
		one = tensuu % 10;

		//十の位処理
		Model* psujiModel = suji[ten][0]->GetModel();
		psujiModel->mPos.y = 0.0f;
		psujiModel->mPos.x = 0.0f;
		Set(suji[ten][0], true, 1, 1, 1, 2.0f);

		//一の位処理
		psujiModel = suji[one][1]->GetModel();
		psujiModel->mPos.y = 0.0f;
		psujiModel->mPos.x = 0.1f;
		Set(suji[one][1], true, 1, 1, 1, 2.0f);

	}
	if (gresult == GAMEOVER)
	{
		Set(gameover, true, 1, 1, 1, 1.0f);
	}

	Set(plessen, true, 1, 1, 1, 1.0f);

	//リターンキーを押すとタイトル画面に遷移
	if (Input_GetKeyDown(VK_RETURN))
	{
		gNowScene = TITLE;
	}


}

void SerectUpdate()
{

	//初期化
	for (int len = 0; len < SUJISUU; len++)
	{
		for (int sen = 0; sen < SUJIHYOUJI; sen++)
		{
			Set(suji[len][sen], false, 1, 1, 1, 1.0f);
		}
	}

	//リターンキーを押すとタイトル画面に遷移
	if (Input_GetKeyDown(VK_RETURN))
	{
		gNowScene = STAGE;
	}


	Model* pModel = yajirusi->GetModel();

	if (Input_GetKeyDown('A'))
	{
		pModel->mRotate.z = -90.0f;
	}
	else if (Input_GetKeyDown('D'))
	{
		pModel->mRotate.z = 90.0f;
	}

	Set(tyutori, true, 1, 1, 1, 1.0f);
	Set(gamestart, true, 1, 1, 1, 1.0f);

	if (pModel->mRotate.z == -90.0)
	{
		Set(gamestart, true, 1, 0, 0, 1.0f);
		gsere = GAME;
	}
	if (pModel->mRotate.z == 90.0)
	{
		Set(tyutori, true, 1, 0, 0, 1.0f);
		gsere = TYUTO;
	}

	

	if (gmaeScene == TITLE)
	{
		Set(title, false, 1, 1, 1, 1.0f);

		Set(plessen, false, 1, 1, 1, 1.0f);

		Set(serect, true, 1, 1, 1, 1.0f);
	
		Set(yajirusi, true, 1, 1, 1, 1.0f);
		gmaeScene = SERECT;
	}

	//リターンキーを押すと画面に遷移
	if (Input_GetKeyDown(VK_RETURN))
	{
		if (gsere == GAME)
		{
			gNowScene = STAGE;
		}
		if (gsere == TYUTO)
		{
			gNowScene = TYUTORIAL;
		}
	}
}

void TyutoUpdate()
{

	static int next = 0;
	if (Input_GetKeyTrigger(VK_SPACE))
	{
		next++;
	}

	// キャラクター移動
	// キャラクターが向いている方向に前進する
	// 向き変更＝ADキー　前進＝Wキー
	// 「前向きベクトル」を計算する
	Model* ptori = gptori->GetModel();

	static float tilt = 0;
	// 鳥の方向転換
	if (Input_GetKeyDown('W'))
	{
		if (ptori->mRotate.z < 90)
		{
			ptori->mRotate.z += CHANGESPEED;
			tilt += 1;
		}
	}
	else if (Input_GetKeyDown('S'))
	{
		if (ptori->mRotate.z > -90)
		{
			ptori->mRotate.z -= CHANGESPEED;
			tilt -= 1;
		}
	}
	else if (Input_GetKeyDown('A'))
	{
		ptori->mRotate.y -= CHANGESPEED;
		if (ptori->mRotate.x > -90)
			ptori->mRotate.x -= CHANGESPEED;
	}
	else if (Input_GetKeyDown('D'))
	{
		ptori->mRotate.y += CHANGESPEED;
		if (ptori->mRotate.x < 90)
			ptori->mRotate.x += CHANGESPEED;
	}
	else
	{
		if (ptori->mRotate.x < 0)
			ptori->mRotate.x += CHANGESPEED;
		if (ptori->mRotate.x > 0)
			ptori->mRotate.x -= CHANGESPEED;
	}

	//鳥の速さ
	gptori->mSpeed = SPEED;


	//傾き計算
	XMFLOAT3 forwardVec = gptori->GetForwardVector();
	if (tilt < 0)
	{
		//ptori->mPos.x = ptori->mPos.x + forwardVec.x * 0.001f;
		ptori->mPos.y = ptori->mPos.y + 0.0009f;
		//ptori->mPos.z = ptori->mPos.z + forwardVec.z * 0.001f;
	}
	if (tilt > 0)
	{
		//ptori->mPos.x = ptori->mPos.x + forwardVec.x * 0.001f;
		ptori->mPos.y = ptori->mPos.y - 0.0009f;
		//ptori->mPos.z = ptori->mPos.z + forwardVec.z * 0.001f;
	}


	
	if (gmaeScene == SERECT)
	{
		Set(tyutori, false, 1, 1, 1, 1.0f);
		Set(gamestart, false, 1, 1, 1, 1.0f);
		Set(yajirusi, false, 1, 1, 1, 1.0f);
		Set(serect, false, 1, 1, 1, 1.0f);
		gresult = NONE2;
		Model* toriModel = gptori->GetModel();
		toriModel->mPos.x = -1000;
		toriModel->mPos.y = TORIY;
		toriModel->mPos.z = -1000;
		toriModel->mRotate.y = TORIROTEY;
		gmaeScene = TYUTORIAL;
	}

	for (int len = 0; len < next; len++)
	{
		Set(tyuto[len], false, 1, 1, 1, 1.0f);
	}
	Set(tyuto[next], true, 1, 1, 1, 1.0f);

	if (next == 4)
	{
		gNowScene = STAGE;
	}
}


void Set(GameObject* a,bool b,float _c,float _d,float _e,float _f)
{
	Model* pModel = a->GetModel();
	pModel->Set2dRender(b); // 2Dモードで表示する設定
	pModel->SetDiffuse(XMFLOAT4(_c, _d, _e, _f)); //マテリアル色設定
}


