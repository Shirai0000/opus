#undef UNICODE  // Unicode�ł͂Ȃ��A�}���`�o�C�g�������g��

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
#include <map> // �A�z�z��
#include <vector> // �ϔz��
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

#pragma comment (lib, "winmm.lib") // timeGetTime�֐��̂���

// �}�N����`
#define CLASS_NAME    "DX21Smpl"// �E�C���h�E�N���X�̖��O
#define WINDOW_NAME  "�X�P���g���v���O����"// �E�B���h�E�̖��O

#define SCREEN_WIDTH (1024)	// �E�C���h�E�̕�
#define SCREEN_HEIGHT (576+30)	// �E�C���h�E�̍���


#define SPEED         (0.004) //�X�s�[�h
#define CHANGESPEED  (0.30) //�����]�����̑��x
#define BIRUSUU      (36)   //�r���̐�
#define BIRU2SUU     (1)   //�r��2�̐�
#define CHARASUU     (30)  //�L������
#define YUKISUU      (800)  //��̐�
#define YUKIHANI     (70)   //����~�炷�͈�
#define YUKISPEED    (0.05)  //����~�炷�X�s�[�h
#define YUKITAKASA     (10)
#define KUSASUU       (100)  //���̐�
#define DISKSUU        (100)  //�f�B�X�N�̐�
#define SUJISUU         (13)  //�����̐�
#define SUJIHYOUJI       (6)  //�\�����鐔���̐�
#define SUJIUV          (0.0769230769230769)
#define TIMELIMIT       (180)
#define TORIHP           (3)
#define TORIX             (-3.5)     //���̏���X
#define TORIY             (1.0)     //���̏���Y
#define TORIZ             (-3.5)     //���̏���Z
#define TORIROTEY         (90)       //���̏����p�xY
#define TORIROTEZ           (0)       //���̏����p�xZ
#define MUTEKI             (5)        //���G����
#define TAKASA             (7)
#define RIAL                (4)      //�`���[�g���A���̐�
#define STARTCOUNT           (5)    //�J�E���g�_�E��
#define TEKISUU              (10)   //�G�̐�
#define BIRUMAYOKO           (5)
#define BIRUMATATE            (5)



// �\���̂̒�`


// �֐��̃v���g�^�C�v�錾
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// �Q�[���̉�ʕ`��̊֐�
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


// ��ʑJ�ڊ֘A
enum SCENE_ID
{
	NONE,  // �ǂ̉�ʂł��Ȃ�
	TITLE, // �^�C�g�����
	STAGE, // �X�e�[�W���
	RESULT, //�@���U���g���
	SERECT,  //�Z���N�g���
	TYUTORIAL
};

enum CLEAR_ID
{
	NONE2,         //�ǂ̉�ʂł��Ȃ�
	CLEAR,        //�N���A���
	GAMEOVER,     //�Q�[���I�[�o�[���
};

enum SERECT_ID
{
	NONE3,  //�ǂ̉�ʂł��Ȃ�
	GAME,   //�Q�[��
	TYUTO,  //�`���[�g���A��
};



SCENE_ID gNowScene = TITLE;         //���̉��ID�����ϐ�

SCENE_ID gmaeScene = TITLE;         //�O�̉��ID�����ϐ�

CLEAR_ID gresult = NONE2;

SERECT_ID gsere = NONE3;


int tensuu;


// �O���[�o���ϐ��̐錾

// ���_�o�b�t�@�p�̕ϐ�
ID3D11Buffer* gpVertexBuffer;

// ���_�������ϐ�
int gNumVertex;

// �e�N�X�`���p�̕ϐ�
ID3D11ShaderResourceView* gpTextureHalOsaka; // HAL OSAKA


extern ID3D11Buffer* gpConstBuffer;

using namespace DirectX;

// GameObject�N���X�̕ϐ�
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

// �e�Ǘ��p�z��
GameObjectVector gShotManager;

// �G�t�F�N�g�Ǘ��p�z��
GameObjectVector gEffectManager;

// ���f���}�l�[�W���[
// �A�z�z�񁁓Y�����ɐ����ȊO���g����z��
// �e���v���[�g���g���Ƃ��ɓ����̌^�����߂�
// map�̏ꍇ�A�O���Y�����^�A��낪�i�[����v�f�̌^
std::map<std::string, ModelData> gModelManager;


// Camera�N���X�̕ϐ�
Camera* gpCamera;

// �f���^�^�C���p�̕ϐ�
DWORD gDeltaTime;

//��ʗp�ϐ�
#include "SceneTitle.h"

IScene* gpActiveScene = new SceneTitle();

#define NMAX   (64)             //���W���i�[����ő�l     


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

// �r���{�[�h�p�̃|���S�����쐬���A�e�N�X�`�����ǂݍ���
ModelData CreateSquarePolygon(float width, float height, float uvlowwidth,float uvlow,float uvWidth, float uvHeight, const wchar_t* texFile)
{
	// ���f�����_�f�[�^�쐬
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

	modelData.mNumVertex = sizeof(vx) / sizeof(ModelVertex); // ���_�����v�Z

	// ���f���p�̒��_�o�b�t�@�쐬
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.ByteWidth = sizeof(vx);
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	// �o�b�t�@�̏����l�w��
	D3D11_SUBRESOURCE_DATA initialVertexData;
	// ���_�o�b�t�@�̏����l
	initialVertexData.pSysMem = vx;
	// ���_�o�b�t�@�ł͎g�p���Ȃ�
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

// WinMain�֐������
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

	RegisterClassEx(&wc); // Windows�ɃE�C���h�E����o�^

	HWND hWnd; // H=Handle=�|�C���^ WND=Window
	hWnd = CreateWindowEx(0,// �g���E�B���h�E�X�^�C��
		CLASS_NAME,// �E�B���h�E�N���X�̖��O
		WINDOW_NAME,// �E�B���h�E�̖��O
		WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,// �E�B���h�E�X�^�C��
		CW_USEDEFAULT,// �E�B���h�E�̍���w���W
		CW_USEDEFAULT,// �E�B���h�E�̍���x���W 
		SCREEN_WIDTH,// �E�B���h�E�̕�
		SCREEN_HEIGHT,// �E�B���h�E�̍���
		NULL,// �e�E�B���h�E�̃n���h��
		NULL,// ���j���[�n���h���܂��͎q�E�B���h�EID
		hInstance,// �C���X�^���X�n���h��
		NULL);// �E�B���h�E�쐬�f�[�^

	// �w�肳�ꂽ�E�B���h�E�̕\����Ԃ�ݒ�(�E�B���h�E��\��)
	ShowWindow(hWnd, nCmdShow);
	// �E�B���h�E�̏�Ԃ𒼂��ɔ��f(�E�B���h�E�̃N���C�A���g�̈���X�V)
	UpdateWindow(hWnd);

	// Direct3D�̏������֐����Ăяo��
	Direct3D_Init(hWnd);

	Game_Init();

	

	MSG msg;
	// ���C�����[�v
	for (;;) {
		// �O��̃��[�v���烆�[�U�[���삪�����������ׂ�
		BOOL doesMessageExist = PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);

		if (doesMessageExist)
		{
			// �ԐړI�ɃE�C���h�E�v���V�[�W�����Ăяo��
			DispatchMessage(&msg);

			// �A�v���I�����߂�����
			if (msg.message == WM_QUIT) {
				break;
			}
		}
		else
		{
			// �f���^�^�C���̌v��
			static DWORD lastTime = timeGetTime(); // �O��v�����̎���
			timeBeginPeriod(1); // ���x���P�~���b�ɏグ��
			DWORD nowTime = timeGetTime(); // ���݂̎���
			timeEndPeriod(1); // ���x�����ɖ߂�
			gDeltaTime = nowTime - lastTime; // �������f���^�^�C��
			lastTime = nowTime; // �O��v�����ԂƂ��ĕۑ�

			// �Q�[�����[�v
			Game_Update(); // �Q�[������
			Game_Draw();   // �Q�[���`��
			Input_Refresh(); // �L�[��Ԃ̍X�V
		}
	}

	Game_Release();
	// Direct3D�̉���֐����Ăяo��
	Direct3D_Release();

	UnregisterClass(CLASS_NAME, hInstance);

	return (int)msg.wParam;
}


// �E�C���h�E�v���V�[�W���֐������
// ���֐�������̂̓O���[�o���̈�(=�ǂ̊֐��̒��ł��Ȃ��ꏊ)�����I
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// uMsg�i���̊֐��̑�2�����j���A���[�U�[�����ID���
	switch (uMsg)
	{
	case WM_DESTROY:// �E�B���h�E�j���̃��b�Z�[�W
		PostQuitMessage(0);// �gWM_QUIT�h���b�Z�[�W�𑗂�@���@�A�v���I��
		break;

	case WM_CLOSE:  // x�{�^���������ꂽ��
		DestroyWindow(hWnd);  // �gWM_DESTROY�h���b�Z�[�W�𑗂�
		break;

	case WM_LBUTTONDOWN: // ���N���b�N���ꂽ�Ƃ�
		Input_SetKeyDown(VK_LBUTTON);
		break;

	case WM_LBUTTONUP: // ���N���b�N���ꂽ�Ƃ�
		Input_SetKeyUp(VK_LBUTTON);
		break;

	case WM_RBUTTONDOWN: // ���N���b�N���ꂽ�Ƃ�
		Input_SetKeyDown(VK_RBUTTON);
		break;

	case WM_RBUTTONUP: // ���N���b�N���ꂽ�Ƃ�
		Input_SetKeyUp(VK_RBUTTON);
		break;

	case WM_MOUSEMOVE: // �}�E�X�J�[�\�����������Ƃ�
		break;

	case WM_KEYDOWN:
		// �L�[�������ꂽ���̃��A�N�V����������
		// ESC�������ꂽ�̂��ǂ����`�F�b�N
		if (LOWORD(wParam) == VK_ESCAPE)
		{
			// ���b�Z�[�W�{�b�N�X�ŏC���m�F
			int result;
			result = MessageBox(NULL, "�I�����Ă�낵���ł����H",
				"�I���m�F", MB_YESNO | MB_ICONQUESTION);
			if (result == IDYES) // �u�͂��v�{�^���������ꂽ��
			{
				// x�{�^���������ꂽ�̂Ɠ������ʂ𔭊�����
				PostMessage(hWnd, WM_CLOSE, wParam, lParam);
			}
		}
		Input_SetKeyDown(LOWORD(wParam));
		break;

	case WM_KEYUP: // �L�[�������ꂽ�C�x���g
		Input_SetKeyUp(LOWORD(wParam));
		break;

	default:
		// ���case�ȊO�̏ꍇ�̏��������s
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
		break;
	}

	return 0;
}

void Game_Init()
{
	// �萔�o�b�t�@�쐬
	// �R���X�^���g�o�b�t�@�Ƃ��č쐬���邽�߂̏��ݒ�
	D3D11_BUFFER_DESC contstat_buffer_desc;
	contstat_buffer_desc.ByteWidth = 512;	// �o�b�t�@�̃T�C�Y�i4x4�s��x4�j
	contstat_buffer_desc.Usage = D3D11_USAGE_DYNAMIC;		// �g�p���@
	contstat_buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;	// �o�b�t�@�̎��(�R���X�^���g�o�b�t�@)
	contstat_buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;			// CPU�A�N�Z�X�ݒ�
	contstat_buffer_desc.MiscFlags = 0;				// ���̑��̃I�v�V����
	contstat_buffer_desc.StructureByteStride = 0;			// �\���̃T�C�Y(�s����g���������0�ł����삷�邱�Ƃ����؂���)

	Direct3D_Get()->device->CreateBuffer(&contstat_buffer_desc,
		nullptr, &gpConstBuffer);

	// �J�����̍쐬
	gpCamera = new BackCamera();
	Camera::mMainCamera = gpCamera;
	// �����l�ݒ�
	// ���ӁFeye��focus���������ƃ_��
	// ���ӁFup��xyz�S�ă[�����ƃ_��
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

	CI::Setmap(map3);   //�}�b�v�����Z�b�g


	// ���f���ǂݍ���
	ObjModelLoader loader;
	gModelManager["cottage"] = loader.Load(
		"assets/cottage.obj", L"assets/cottage.png");

	// �����f���ǂݍ���
	loader = ObjModelLoader();
	gModelManager["gun"] = loader.Load(
		"assets/tori.obj", L"assets/�X�e�����X.jpg");

	loader = ObjModelLoader();
	gModelManager["teki"] = loader.Load(
		"assets/teki.obj", L"assets/�X�e�����X.jpg");

	//�r�����f���ǂݍ���
	loader = ObjModelLoader();
	gModelManager["biru"] = loader.Load(
		"assets/biru.obj", L"assets/�R���N���[�g2.jpg");

	//�B���f���ǂݍ���
	loader = ObjModelLoader();
	gModelManager["ori"] = loader.Load(
		"assets/ori.obj", L"assets/�X�e�����X.jpg");

	//�r��2���f���ǂݍ���
	loader = ObjModelLoader();
	gModelManager["biru2"] = loader.Load(
		"assets/biru2.obj", L"assets/�R���N���[�g2.jpg");

	//�󃂃f���ǂݍ���
	loader = ObjModelLoader();
	gModelManager["sora"] = loader.Load(
		"assets/sora.obj", L"assets/�X�e�����X.jpg");

	//�B���������f���ǂݍ���
	loader = ObjModelLoader();
	gModelManager["oritori"] = loader.Load(
		"assets/oritori.obj", L"assets/�X�e�����X.jpg");

	//�f�B�X�N���f���ǂݍ���
	loader = ObjModelLoader();
	gModelManager["disk"] = loader.Load(
		"assets/disk.obj", L"assets/�X�e�����X.jpg");

	//�G���f���ǂݍ���
	loader = ObjModelLoader();
	gModelManager["teki"] = loader.Load(
		"assets/block.obj", L"assets/�X�e�����X.jpg"
	);

	////�����f���ǂݍ���
	//loader = ObjModelLoader();
	//gModelManager["disk"] = loader.Load(
	//	"assets/kusa.obj", L"assets/yukijimen.png");

	// ���pModel�I�u�W�F�N�g����
	gptori = new NormalObject();
	Model* pGunModel = gptori->GetModel();
	pGunModel->SetModelData(gModelManager["gun"]);
	pGunModel->SetScale(0.3f);
	pGunModel->mPos.x = TORIX;
	pGunModel->mPos.y = TORIY;
	pGunModel->mPos.z = TORIZ;
	pGunModel->mRotate.y = TORIROTEY;
	pGunModel->mCamera = gpCamera;

	//�����蔻��ɕK�v
	HitSphere* pHit = gptori->GetHit();
	pHit->SetHankei(0.8f);// �����蔻��̔��a��ݒ�
	pHit->SetHigh(0.8f);
	pHit->SetWidth(0.9f);

	// �n�ʃ��f���ǂݍ���
	loader = ObjModelLoader();
	gModelManager["ground1"] = loader.Load(
		"assets/ground1.obj", L"assets/yukijimen.png"
	);

	// �n�ʐ���
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

	// �e���f���ǂݍ���
	loader = ObjModelLoader();
	gModelManager["shot"] = loader.Load(
		"assets/billboard.obj", L"assets/effect000.jpg"
	);

	

	// �e�p�I�u�W�F�N�g����
	gpShot = new BillboardObject();
	Model* pShotModel = gpShot->GetModel();
	pShotModel->SetModelData(gModelManager["shot"]);
	pShotModel->SetScale(0.2f);
	pShotModel->mPos.y = 0.2f;
	pShotModel->mPos.z = 1.0f;
	pShotModel->mCamera = gpCamera;

	// 2D�L�����p�|���S������
	gModelManager["2Dchar"] =
		CreateSquarePolygon(1.0f, 1.2f,0.0f,0.0f, 0.33f, 0.25f,
			L"assets/char01.png");


	// 2D��p�|���S������
	gModelManager["2Dyuki"] =
		CreateSquarePolygon(1.0f, 1.0f,0.0f,0.0f, 1.0f, 1.0f,
			L"assets/yuki.png");

	// 2D��p�I�u�W�F�N�g����
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
		// 2D�L�����p�I�u�W�F�N�g����
		gp2Dchar[len] = new BillboardObject();
		Model* p2DModel = gp2Dchar[len]->GetModel();
		p2DModel->SetModelData(gModelManager["2Dchar"]);
		p2DModel->SetScale(1.0f);
		p2DModel->mPos.y = 0.6f;
		p2DModel->mPos.z = 5.0f;
		p2DModel->mPos.x = 5.0+len*3;
		p2DModel->mCamera = gpCamera;
		pHit = gp2Dchar[len]->GetHit();
		pHit->SetHankei(0.8f);// �����苅�̔��a��ݒ�
		gObjectList.emplace_back(gp2Dchar[len]);
	}

	// �G�pModel�I�u�W�F�N�g����
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
		pHit = gpteki[len]->GetHit();	//�����蔻��ɕK�v
		pHit->SetHankei(0.8f);// �����蔻��̔��a��ݒ�
		pHit->SetHigh(0.5f);
		pHit->SetWidth(0.5f);
		gObjectList.emplace_back(gpteki[len]);
	}


	// �B�pModel�I�u�W�F�N�g����
	gpori = new NormalObject();
	Model* pOriModel = gpori->GetModel();
	pOriModel->SetModelData(gModelManager["ori"]);
	pOriModel->SetScale(0.5f);
	pOriModel->mPos.y = 0.4f;
	pOriModel->mPos.z = 10.0f;
	pOriModel->mPos.x = 10.0f;
	pOriModel->mRotate.y = 90.0f;
	pOriModel->mCamera = gpCamera;
	pHit = gpori->GetHit();	//�����蔻��ɕK�v
	pHit->SetHankei(0.8f);// �����蔻��̔��a��ݒ�
	pHit->SetHigh(0.5f);
	pHit->SetWidth(0.5f);

	// �f�B�X�N�pModel�I�u�W�F�N�g����
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
		pHit = gpdisk[len]->GetHit();	//�����蔻��ɕK�v
		pHit->SetHankei(0.8f);// �����蔻��̔��a��ݒ�
		pHit->SetHigh(0.5f);    //�����蔻��̍�����ݒ�
		pHit->SetWidth(0.5f);   //�����蔻��̍L����ݒ�
		gObjectList.emplace_back(gpdisk[len]);
	}

	//for (int len = 0; len < KUSASUU; len++)
	//{
	//	// �f�B�X�N�pModel�I�u�W�F�N�g����
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

	// ��pModel�I�u�W�F�N�g����
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
	

	// �r���p�I�u�W�F�N�g����

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
 					pHit = gpbiru[birunum]->GetHit();	//�����蔻��ɕK�v
					pHit->SetHankei(5.0f);// �����蔻��̔��a��ݒ�
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
	//pHit = gpbiru[0]->GetHit();	//�����蔻��ɕK�v
	//pHit->SetHankei(5.0f);// �����蔻��̔��a��ݒ�
	//pHit->SetHigh(7.0f);
	//pHit->SetWidth(0.6f);
	//gObjectList.emplace_back(gpbiru[0]);

	//�r��2�p�I�u�W�F�N�g�쐬
	for (int i = 0; i < BIRU2SUU; i++)
	{
		gpbiru2[i] = new NormalObject();
		Model* pbiru2Model = gpbiru2[i]->GetModel();
		pbiru2Model->SetModelData(gModelManager["biru2"]);
		pbiru2Model->mCamera = gpCamera;
		pHit = gpbiru2[i]->GetHit();	//�����蔻��ɕK�v
		pHit->SetHankei(5.0f);// �����蔻��̔��a��ݒ�
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


	//// �R�e�[�W�p�I�u�W�F�N�g����
	//for (int i = 0; i < 5; i++)
	//{
	//	gpCottage = new NormalObject();
	//	Model* pCottageModel = gpCottage->GetModel();
	//	pCottageModel->SetModelData(gModelManager["cottage"]); // 3D�f�[�^���Z�b�g����
	//	pCottageModel->SetScale(0.002f);
	//	pCottageModel->mPos.x = -30.0f + i * 6.5f;
	//	pCottageModel->mPos.z = 5.0f;
	//	pCottageModel->mPos.y = 0.0f;
	//	gObjectList.emplace_back(gpCottage);
	//}

	//�����N���X
	gModelManager["explosion"] = CreateSquarePolygon(1.0f, 1.0f,0.0f,0.0f, 0.25f, 0.25f, L"assets/explosion.png");
	GameObject* tmp = new Explosion(4,4);
   
	Model* pModel = tmp->GetModel();
	pModel->SetModelData(gModelManager["explosion"]);
	gObjectList.emplace_back(tmp);


	//�����N���X
	gModelManager["baku"] = CreateSquarePolygon(1.0f, 1.0f, 0.0f, 0.0f, 0.1f, 1.0f, L"assets/baku.png");

	tmp = new Explosion(8, 1);
	pModel = tmp->GetModel();
	pModel->SetModelData(gModelManager["baku"]);
	gObjectList.emplace_back(tmp);



	//�^�C�g���摜�𐶐�
	gModelManager["title"] = CreateSquarePolygon(2.0f, 2.0f,0.0f,0.0f, 1.0f, 1.0f, L"assets/�^�C�g��.png");
    title = new NormalObject();
	pModel = title->GetModel();
	pModel->SetModelData(gModelManager["title"]);
	pModel->Set2dRender(false); // 2D���[�h�ŕ\������ݒ�
	pModel->SetDiffuse(XMFLOAT4(1, 0, 0, 1.0f)); //�}�e���A���F�ݒ�
	gObjectList.emplace_back(title);


	//�����摜�𐶐�
	for (int len = 0; len < SUJISUU; len++)
	{
		for (int sen = 0; sen < SUJIHYOUJI; sen++)
		{
			gModelManager["suji"] = CreateSquarePolygon(0.1f, 0.1f, SUJIUV*len, 0.0f, 0.07 + (SUJIUV*len), 1.0f, L"assets/suji.png");
			suji[len][sen] = new NormalObject();
			pModel = suji[len][sen]->GetModel();
			pModel->SetModelData(gModelManager["suji"]);
			pModel->Set2dRender(false); // 2D���[�h�ŕ\������ݒ�
			pModel->SetDiffuse(XMFLOAT4(1, 1, 1, 1.0f)); //�}�e���A���F�ݒ�
			pModel->mPos.y = 0.8f;
			pModel->mPos.x = 0.9f;
			gObjectList.emplace_back(suji[len][sen]);
		}
	}

	//���v�摜�𐶐�
	gModelManager["watch"] = CreateSquarePolygon(0.3f, 0.3f, 0.0f, 0.0f, 1.0f, 1.0f, L"assets/�^�C��.png");
	watch = new NormalObject();
	pModel = watch->GetModel();
	pModel->SetModelData(gModelManager["watch"]);
	pModel->Set2dRender(false); // 2D���[�h�ŕ\������ݒ�
	pModel->SetDiffuse(XMFLOAT4(1, 1, 1, 1.0f)); //�}�e���A���F�ݒ�
	pModel->mPos.y = 0.8f;
	pModel->mPos.x = -0.6f;
	gObjectList.emplace_back(watch);





	//�v���[�Y�G���^�[�摜�𐶐�
	gModelManager["enter"] = CreateSquarePolygon(0.3f, 0.3f, 0.0f, 0.0f, 1.0f, 1.0f, L"assets/PressEnter.png");
	plessen = new NormalObject();
	pModel = plessen->GetModel();
	pModel->SetModelData(gModelManager["enter"]);
	pModel->Set2dRender(false); // 2D���[�h�ŕ\������ݒ�
	pModel->SetDiffuse(XMFLOAT4(1, 1, 1, 1.0f)); //�}�e���A���F�ݒ�
	pModel->mPos.x = 0.0f;
	pModel->mPos.y = -0.3f;
	gObjectList.emplace_back(plessen);

	//�f�B�X�N�摜�𐶐�
	gModelManager["aicon"] = CreateSquarePolygon(0.3f, 0.3f, 0.0f, 0.0f, 1.0f, 1.0f, L"assets/�f�B�X�N.png");
	aicon = new NormalObject();
	pModel = aicon->GetModel();
	pModel->SetModelData(gModelManager["aicon"]);
	pModel->Set2dRender(false); // 2D���[�h�ŕ\������ݒ�
	pModel->SetDiffuse(XMFLOAT4(1, 1, 1, 1.0f)); //�}�e���A���F�ݒ�
	pModel->mPos.x = 0.6f;
	pModel->mPos.y = 0.8f;
	gObjectList.emplace_back(aicon);

	//�Q�[���I�[�o�[�摜�𐶐�
	gModelManager["gameover"] = CreateSquarePolygon(2.0f, 2.0f, 0.0f, 0.0f, 1.0f, 1.0f, L"assets/�Q�[���I�[�o�[.png");
	gameover = new NormalObject();
	pModel = gameover->GetModel();
	pModel->SetModelData(gModelManager["gameover"]);
	pModel->Set2dRender(false); // 2D���[�h�ŕ\������ݒ�
	pModel->SetDiffuse(XMFLOAT4(1, 1, 1, 1.0f)); //�}�e���A���F�ݒ�
	gObjectList.emplace_back(gameover);


	//�N���A�摜�𐶐�
	gModelManager["clear"] = CreateSquarePolygon(2.0f, 2.0f, 0.0f, 0.0f, 1.0f, 1.0f, L"assets/result.png");
	clear = new NormalObject();
	pModel = clear->GetModel();
	pModel->SetModelData(gModelManager["clear"]);
	pModel->Set2dRender(false); // 2D���[�h�ŕ\������ݒ�
	pModel->SetDiffuse(XMFLOAT4(1, 1, 1, 1.0f)); //�}�e���A���F�ݒ�
	gObjectList.emplace_back(clear);

	//�`���[�g���A���摜�𐶐�
	gModelManager["tyuuto"] = CreateSquarePolygon(1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, L"assets/�`���[�g���A��.png");
	tyutori = new NormalObject();
	pModel = tyutori->GetModel();
	pModel->SetModelData(gModelManager["tyuuto"]);
	pModel->Set2dRender(false); // 2D���[�h�ŕ\������ݒ�
	pModel->SetDiffuse(XMFLOAT4(1, 1, 1, 1.0f)); //�}�e���A���F�ݒ�
	pModel->mPos.x = 0.5f;

	gObjectList.emplace_back(tyutori);

	//�Q�[���X�^�[�g�摜�𐶐�
	gModelManager["start"] = CreateSquarePolygon(1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, L"assets/�Q�[���X�^�[�g.png");
	gamestart = new NormalObject();
	pModel = gamestart->GetModel();
	pModel->SetModelData(gModelManager["start"]);
	pModel->Set2dRender(false); // 2D���[�h�ŕ\������ݒ�
	pModel->SetDiffuse(XMFLOAT4(1, 1, 1, 1.0f)); //�}�e���A���F�ݒ�
	pModel->mPos.x = -0.5f;
	
	gObjectList.emplace_back(gamestart);

	//���摜�𐶐�
	gModelManager["yajirusi"] = CreateSquarePolygon(0.3f, 0.3f, 0.0f, 0.0f, 1.0f, 1.0f, L"assets/�₶�邵.png");
	yajirusi = new NormalObject();
	pModel = yajirusi->GetModel();
	pModel->SetModelData(gModelManager["yajirusi"]);
	pModel->Set2dRender(false); // 2D���[�h�ŕ\������ݒ�
	pModel->SetDiffuse(XMFLOAT4(1, 1, 1, 1.0f)); //�}�e���A���F�ݒ�
	gObjectList.emplace_back(yajirusi);

	//�Z���N�g�摜�𐶐�
	gModelManager["serect"] = CreateSquarePolygon(2.0f, 2.0f, 0.0f, 0.0f, 1.0f, 1.0f, L"assets/serect.png");
	serect = new NormalObject();
	pModel = serect->GetModel();
	pModel->SetModelData(gModelManager["serect"]);
	pModel->Set2dRender(false); // 2D���[�h�ŕ\������ݒ�
	pModel->SetDiffuse(XMFLOAT4(1, 1, 1, 1.0f)); //�}�e���A���F�ݒ�
	gObjectList.emplace_back(serect);

	//CSV�t�@�C������MAP�f�[�^��ǂݍ���
	Csv csv{ "map01.csv" };	//csv�t�@�C�����w�肵��"Csv"�N���X�ϐ����쐬�B
	int data_size = csv.read();	//CSV�t�@�C����ǂݍ��ށB�߂�l�͓ǂݍ��񂾃f�[�^���iint�f�[�^�̐��j
	if (data_size < 0) {
		//read()�̖߂�l���O��}�C�i�X�l�Ȃ�G���[�B

	}


	// �J�����̒Ǐ]�^�[�Q�b�g���w��
	//((BackCamera*)gpCamera)->SetTarget(gptori);  // C�X�^�C���L���X�g
	dynamic_cast<BackCamera*>(gpCamera)->SetTarget(gptori); // C++�L���X�g
}



void Game_Draw()
{
	// DIRECT3D�\���̂ɃA�N�Z�X����
	DIRECT3D* d3d = Direct3D_Get();

	// ��ʃN���A�i�w��F�œh��Ԃ��j
	// �h��Ԃ��F�̎w��i�����F0.0f�`1.0f�j
	float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; //red,green,blue,alpha

	d3d->context->ClearRenderTargetView(d3d->renderTarget, clearColor);

	// Z�o�b�t�@�A�X�e���V���o�b�t�@�N���A
	d3d->context->ClearDepthStencilView(
		d3d->depthStencilView,			// �f�v�X�X�e���V���r���[
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
		1.0f,			// �y�o�b�t�@��1.0�ŃN���A����(0.0f�`1.0f)
		0);				// �X�e���V���o�b�t�@��0�ŃN���A����

	// ���@���O�̕`�揈���������ɏ��� *******

	// �Q�[���I�u�W�F�N�g��`��
	d3d->context->OMSetBlendState(d3d->blendAlpha, NULL, 0xffffffff);// �A���t�@�u�����h

	vector_DrawAll(gObjectList);

	d3d->context->OMSetBlendState(d3d->blendAdd, NULL, 0xffffffff);// ���Z����
	// �e�Ǘ��z��̒��g��S��Draw����
	vector_DrawAll(gShotManager);

	vector_DrawAll(gEffectManager);

	gpActiveScene->Draw();

	// �_�u���o�b�t�@�̐؂�ւ�
	d3d->swapChain->Present(0, 0);
}

void Game_Update()
{
	// �f���^�^�C�����z��O�̒l�ɂȂ����ꍇ�̏���
	if (gDeltaTime >= 100)
	{
		gDeltaTime = 0;
	}
	if (gDeltaTime <= 0)
	{
		gDeltaTime = 1;
	}



	//�V�[���J��
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



	// �J�����ړ��ϐ�
	static float angle = 0.5f; // ��]�p�x
	static float zoom = 3.0f;  // �Y�[��

	// �@�J�����̈ʒu���L�[����ňړ�����
	if (Input_GetKeyDown(VK_RIGHT))
	{
		angle += 0.5;
	}
	if (Input_GetKeyDown(VK_LEFT))
	{
		angle -= 0.5f;
	}
	// �Y�[������
	if (Input_GetKeyDown(VK_UP))
		zoom -= 0.01f * gDeltaTime;
	if (Input_GetKeyDown(VK_DOWN))
		zoom += 0.01f * gDeltaTime;

	// �A�J�����̒����_�𒆐S�ɃJ��������]����

	// �J�����ʒuX�@���@sinf(�p�x���W�A��)
	// �J�����ʒuZ�@���@cosf(�p�x���W�A��)
	// ���_�𒆐S�ɔ��a1.0f�̉~����̓_�����߂�
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
	// �J���������_���R�e�[�W�̈ʒu�ɂ���
	//gpCamera->SetFocus(pCottageModel->mPos);
	gpCamera->SetFocus(ptoriModel->mPos);

	

	vector_UpdateAll(gObjectList);

	// �e�Ǘ��z��̒��g��S��Update����
	vector_UpdateAll(gShotManager);

	// �e�̉������
	for (int i = 0; i < gShotManager.size(); i++)
	{
		// (a)�J�����̈ʒu
		XMFLOAT3 cameraPos = gpCamera->mEye;
		// (b)�e�̈ʒu
		XMFLOAT3 shotPos = gShotManager[i]->GetModel()->mPos;
		// (b)��(a)�x�N�g��
		XMVECTOR abVector =
			XMLoadFloat3(&cameraPos) - XMLoadFloat3(&shotPos);
		// (b)��(a)�x�N�g���̒������v�Z
		XMVECTOR abVecLength = XMVector3Length(abVector);
		float abLength = XMVectorGetX(abVecLength);
		// abLength�������ȏ�Ȃ�e���������
		if (abLength >= 50.0f)
		{
			// erase�֐������ł͒e��delete�͍s���Ȃ�
			delete gShotManager[i];
			// �e�Ǘ��z�񂩂�e���폜
			gShotManager.erase(gShotManager.begin() + i);
		}
	}

	
	vector_UpdateAll(gEffectManager);

	// �Đ����I������G�t�F�N�g������
	for (int i = 0; i < gEffectManager.size(); i++)
	{
		Explosion* e = dynamic_cast<Explosion*>(gEffectManager[i]);
		if (e->IsFinished())
		{
			delete gEffectManager[i];
			// �e�Ǘ��z�񂩂�e���폜
			gEffectManager.erase(gEffectManager.begin() + i);
			i--;
		}
	}

	// �J�����X�V�i�r���[�ϊ��s��v�Z�j
	gpCamera->Update();
}

void Game_Release()
{
	vector_DeleteAll(gObjectList);

	// �e�Ǘ��z��̒��g��S��delete����
	vector_DeleteAll(gShotManager);	

	vector_DeleteAll(gEffectManager);

	COM_SAFE_RELEASE(gpConstBuffer);

	// ���f���}�l�[�W���[�����S���f�������
	for (auto i = gModelManager.begin();//�A�z�z��̐擪���
		i != gModelManager.end();//�A�z�z��̍Ō�����
		i++)
	{
		// first �c �Y����
		// second �c �v�f���̂���
		COM_SAFE_RELEASE(i->second.mSRV);//�e�N�X�`��
		COM_SAFE_RELEASE(i->second.mVertexBuffer);//���_�o�b�t�@
	}
	// �A�z�z��̑S�v�f���폜����i�v�f���O�ɂ���j
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


	//�^�C�g�����S�\��
	Set(title,true,1,1,1,1.0f);

	static float toumei = 0;

	//�v���[�Y�G���^�[�\��
	Set(plessen, true, 1, 1, 1, toumei);

	//�����x��ύX
	toumei += 0.001;
	if(toumei >= 1.0)
	{
		toumei = 0.0;
	}

	//�X�y�[�X�L�[�������ƃZ���N�g��ʂɑJ��
	if (Input_GetKeyDown(VK_SPACE))
	{
		gNowScene = SERECT;
	}

}

void StageUpdate()
{
	static int point = 0;                  //�_��

	static int torihp = TORIHP;            //��HP

	static int limit = TIMELIMIT * 60;     //�^�C�����~�b�g

	static int mutekitime = MUTEKI*60;    //���G����

	static bool atari = false;      //���G�ɂȂ��Ă��邩

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


	//������
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
		mutekitime = MUTEKI * 60;    //���G����
		atari = false;
		gptori->mSpeed = 0; //���̑���
		starttime = STARTCOUNT * 60;
		gmaeScene = STAGE;

	}
	
	////�X�R�A�\��//////////////////////////
	//������
	for (int len = 0; len < SUJISUU; len++)
	{
		for (int sen = 0; sen < SUJIHYOUJI; sen++)
		{
			Set(suji[len][sen], false, 1, 1, 1, 1.0f);
		}
	}

	int one = 0;  //��̈�
	int ten = 0;  //�\�̈�

	ten = point / 10;
	one = point % 10;

	//�\�̈ʏ���
	Model* psujiModel = suji[ten][0]->GetModel();
	psujiModel->mPos.y = 0.8f;
	psujiModel->mPos.x = 0.8f;
	Set(suji[ten][0], true, 1, 1, 1, 1.0f);
	
	//��̈ʏ���
	psujiModel = suji[one][1]->GetModel();
	psujiModel->mPos.y = 0.8f;
	psujiModel->mPos.x = 0.9f;
	Set(suji[one][0], true, 1, 1, 1, 1.0f);
	//////////////////////////////////////////////////////
	
	

	Set(aicon, true, 1, 1, 1, 1.0f);

	Set(watch, true, 1, 1, 1, 1.0f);


	////�^�C�����~�b�g�\��////////////////////

	//�J�E���g�_�E�����I���܂œ����Ȃ�
	if (!((starttime / 60) >= 0))
	{
		limit -= 1;
	}

	int hundred = 0; //�S�̈�

	hundred = (limit / 60) / 100;
	ten = ((limit/60)%100) / 10;
	one = (limit/60) % 10;

	//�S�̈ʏ���
	psujiModel = suji[hundred][2]->GetModel();
	psujiModel->mPos.y = 0.8f;
	psujiModel->mPos.x = -0.5f;
	Set(suji[hundred][2], true, 1, 1, 1, 1.0f);


	//�\�̈ʏ���
	psujiModel = suji[ten][3]->GetModel();
	psujiModel->mPos.y = 0.8f;
	psujiModel->mPos.x = -0.4f;
	Set(suji[ten][3], true, 1, 1, 1, 1.0f);

	//��̈ʏ���
	psujiModel = suji[one][4]->GetModel();
	psujiModel->mPos.y = 0.8f;
	psujiModel->mPos.x = -0.3f;
	Set(suji[one][4], true, 1, 1, 1, 1.0f);
    //////////////////////////////////////


	//�J�E���g�_�E��/////////

	if ((starttime/60) >= 0)
	{
		psujiModel = suji[starttime / 60][5]->GetModel();
		psujiModel->mPos.y = 0.0f;
		psujiModel->mPos.x = 0.0f;
		Set(suji[starttime / 60][5], true, 1, 1, 1, 1.0f);
	}
	/////////////////////////////


	//����~�点�鏈��
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

	// �L�����N�^�[�ړ�
	// �L�����N�^�[�������Ă�������ɑO�i����
	// �����ύX��AD�L�[�@�O�i��W�L�[
	// �u�O�����x�N�g���v���v�Z����
	Model* ptori = gptori->GetModel();

	static float tilt = 0;
	// ���̕����]��
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


	//�J�E���g�_�E�����I���܂œ����Ȃ�
	if (!((starttime / 60) >= 0))
	{
		//���̑���
		gptori->mSpeed = SPEED;
	}

	//�X���v�Z
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

	// �e�̔���
	//f (Input_GetKeyDown(VK_LBUTTON))
	//
	//	// �e�I�u�W�F�N�g����
	//	GameObject* pShot = new BillboardObject();
	//	Model* pShotModel = pShot->GetModel();
	//	pShotModel->SetModelData(gModelManager["shot"]);
	//	pShotModel->SetScale(0.2f);
	//	pShot->GetHit()->SetHankei(0.19f);
	//	
	//	// ���˒n�_�Ɉړ�������
	//	XMFLOAT3 forwardVec = gptori->GetForwardVector();
	//
	//	pShotModel->mPos.x =
	//		pGunModel->mPos.x + forwardVec.x * 0.8f;
	//	pShotModel->mPos.y = pGunModel->mPos.y + 0.2f;
	//	pShotModel->mPos.z =
	//		pGunModel->mPos.z + forwardVec.z * 0.8f;
	//	// �e�ɑ��x��ݒ肷��
	//	pShot->mSpeed = 0.01f;
	//	// �e����ԕ�����ݒ�
	//	pShotModel->mRotate.y = pGunModel->mRotate.y;
	//
	//	// �e�Ǘ��z��ɒǉ�����
	//	gShotManager.emplace_back(pShot);
	//

	HitSphere* ptoriHit = gptori->GetHit();
	
	// �e��NPC�����蔻��
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
			//�r���Ƃ̓����蔻��
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

	//�f�B�X�N�ƃr���̓����蔻��
	for (int len = 0; len < DISKSUU; len++)
	{
		for (int sen = 0; sen < BIRUSUU; sen++)
		{
			HitSphere* pdiskHit = gpdisk[len]->GetHit();
			Model* pDiModel = gpdisk[len]->GetModel();
			//�r���Ƃ̓����蔻��
			if (pdiskHit->IsHit(gpbiru[sen]->GetHit()))
			{
				//�r���Əd�Ȃ��Ă���ꍇ�d�Ȃ�Ȃ��Ȃ�܂ō��W��ύX
				do {
					pDiModel->mPos.y = rand() % TAKASA;
					pDiModel->mPos.z = rand() % YUKIHANI;
					pDiModel->mPos.x = rand() % YUKIHANI;

				} while (pdiskHit->IsHit(gpbiru[sen]->GetHit()));
			}
		
		}
	}


	//�f�B�X�N�Ƃ̓����蔻��
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
		//�n�ʂ�艺�ɂ������ꍇ
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
	
	//�J�E���g�_�E�����I���܂œ����Ȃ�
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
		

	//���Ԃ�����result�ɑJ��
	if (limit == 0)
	{
		gNowScene = RESULT;
		gresult = CLEAR;
		tensuu = point;
	}

	//�Q�[���I�[�o�[
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
	//������
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

		//�_��

		int one = 0;  //��̈�
		int ten = 0;  //�\�̈�

		ten = tensuu / 10;
		one = tensuu % 10;

		//�\�̈ʏ���
		Model* psujiModel = suji[ten][0]->GetModel();
		psujiModel->mPos.y = 0.0f;
		psujiModel->mPos.x = 0.0f;
		Set(suji[ten][0], true, 1, 1, 1, 2.0f);

		//��̈ʏ���
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

	//���^�[���L�[�������ƃ^�C�g����ʂɑJ��
	if (Input_GetKeyDown(VK_RETURN))
	{
		gNowScene = TITLE;
	}


}

void SerectUpdate()
{

	//������
	for (int len = 0; len < SUJISUU; len++)
	{
		for (int sen = 0; sen < SUJIHYOUJI; sen++)
		{
			Set(suji[len][sen], false, 1, 1, 1, 1.0f);
		}
	}

	//���^�[���L�[�������ƃ^�C�g����ʂɑJ��
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

	//���^�[���L�[�������Ɖ�ʂɑJ��
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

	// �L�����N�^�[�ړ�
	// �L�����N�^�[�������Ă�������ɑO�i����
	// �����ύX��AD�L�[�@�O�i��W�L�[
	// �u�O�����x�N�g���v���v�Z����
	Model* ptori = gptori->GetModel();

	static float tilt = 0;
	// ���̕����]��
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

	//���̑���
	gptori->mSpeed = SPEED;


	//�X���v�Z
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
	pModel->Set2dRender(b); // 2D���[�h�ŕ\������ݒ�
	pModel->SetDiffuse(XMFLOAT4(_c, _d, _e, _f)); //�}�e���A���F�ݒ�
}


