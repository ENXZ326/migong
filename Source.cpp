
//########## �w�b�_�[�t�@�C���ǂݍ��� ##########
#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>

//########## �}�N����` ##########
#define GAME_WIDTH	600	//��ʂ̉��̑傫��
#define GAME_HEIGHT	400	//��ʂ̏c�̑傫��
#define GAME_COLOR	32		//��ʂ̃J���[�r�b�g

#define GAME_BACKGOUND		"BACK\\space4.jpg"				//�w�i�摜
#define GAME_BACKGOUND1		""
#define GAME_CHARA_UFO		"CHARA\\UFO_mini.png"	//UFO�̉摜

#define FNT_TANU_PATH	TEXT("MY_FONT\\TanukiMagic.ttf")	//�t�H���g�̏ꏊ
#define FNT_TANU_NAME	TEXT("���ʂ������}�W�b�N")			//�t�H���g�̖��O

#define GAME_WINDOW_NAME	"?????"

#define GAME_FPS_SPEED					   60

#define SET_WINDOW_ST_MODE_DEFAULT			0
#define SET_WINDOW_ST_MODE_TITLE_NONE		1
#define SET_WINDOW_ST_MODE_TITLE_FLAME_NONE	2
#define SET_WINDOW_ST_MODE_FLAME_NONE		3

//########## �񋓌^ ##########
enum GAME_SCENE {
	GAME_SCENE_TITLE,//�^�C�g�����
	GAME_SCENE_PLAY,//�v���C���
	GAME_SCENE_END//�G���h���
};

//########## �\���� ##########
struct STRUCT_GAZOU {
	int Handle;				//�摜�̃n���h��
	char FilePath[128];		//�t�@�C���̃p�X
	int X;					//���̈ʒu
	int Y;					//�c�̈ʒu
	int Width;				//���̃T�C�Y
	int Height;				//�c�̃T�C�Y
	int C_Width;			//���̒��S�ʒu
	int C_Height;			//�c�̒��S�ʒu
	int MoveSpeed;			//�ړ����x
	BOOL IsView;			//�\������
};



//########## ���O�̍Ē�` ##########
typedef STRUCT_GAZOU GAZOU;

//########## �O���[�o���ϐ� ##########
GAZOU	BackGround;				//�w�i�̉摜
GAZOU	UFO1;					//UFO�̉摜
GAZOU	CRAB1;


char AllKeyState[256];			//���ׂẴL�[�̏�Ԃ�����

//FPS�֘A
int StartTimeFps;						//����J�n����
int CountFps;							//�J�E���^
float CalcFps;							//�v�Z����
int SampleNumFps = GAME_FPS_SPEED;		//���ς����T���v����

int HFont_tanu_32;						//�t�H���g�̃n���h��



int GameSceneNow = (int)GAME_SCENE_TITLE;//�ŏ��̃Q�[����ʂ��^�C�g���ɐݒ�

//########## �v���g�^�C�v�錾 ##########

BOOL MY_GAZOU_LOAD(GAZOU *, int, int, const char *);			//�摜��ǂݍ��ސݒ������֐�

VOID MY_DRAW_PLAY_INFO(VOID);

BOOL MY_FONT_CREATE(const char *, int *, int, int, int);		//�t�H���g��ǂݍ��ފ֐�
LRESULT CALLBACK MY_WNDPROC(HWND, UINT, WPARAM, LPARAM);		//����E�B���h�E�v���V�[�W��

VOID MY_ALL_KEYDOWN_UPDATE(VOID);	//�L�[�̓��͏�Ԃ��X�V����֐�

VOID MY_FPS_UPDATE(VOID);			//FPS�l���v���A�X�V����֐�
VOID MY_FPS_DRAW(VOID);				//FPS�l��`�悷��֐�
VOID MY_FPS_WAIT(VOID);				//FPS�l���v�����A�҂֐�
VOID MY_DRAW_PLAY_INFO(VOID);		//�v���C��ʂ̏���`�悷��֐�
VOID MY_GAME_TITLE(VOID);			//�^�C�g����ʂ̊֐�
VOID MY_GAME_END(VOID);				//�G���h��ʂ̊֐�

//########## �v���O�����ōŏ��Ɏ��s�����֐� ##########
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);										//�E�B���h�E���[�h�ɐݒ�
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);			//�w��̐��l�ŉ�ʂ�\������
	SetWindowStyleMode(SET_WINDOW_ST_MODE_DEFAULT);			//�^�C�g���o�[
	//SetWindowStyleMode(SET_WINDOW_ST_MODE_TITLE_NONE);			//�^�C�g���o�[�Ȃ�

	SetMainWindowText(TEXT(GAME_WINDOW_NAME));					//�^�C�g���̕���


	if (DxLib_Init() == -1) { return -1; }						//�c�w���C�u��������������


	SetDrawScreen(DX_SCREEN_BACK);								//Draw�n�֐��͗���ʂɕ`��

	//�摜��ǂݍ���
	if (MY_GAZOU_LOAD(&BackGround, 0, 0, GAME_BACKGOUND) == FALSE) { return -1; }
	if (MY_GAZOU_LOAD(&UFO1, GAME_WIDTH / 2, GAME_HEIGHT / 2, GAME_CHARA_UFO) == FALSE) { return -1; }


	//�������[�v
	while (TRUE)
	{
		if (ProcessMessage() != 0) { break; }	//���b�Z�[�W�����̌��ʂ��G���[�̂Ƃ��A�����I��

		if (ClearDrawScreen() != 0) { break; }	//��ʂ������ł��Ȃ������Ƃ��A�����I��

		MY_ALL_KEYDOWN_UPDATE();				//�����Ă���L�[��Ԃ��� ��

		MY_FPS_UPDATE();	//FPS�̏���[�X�V]

		//�V�[���I��
		switch (GameSceneNow)
		{
		case (int)GAME_SCENE_TITLE://�^�C�g����ʂ̏�����������

			MY_GAME_TITLE();

			break;//�^�C�g����ʂ̏��������܂�

		case (int)GAME_SCENE_PLAY:

			if (AllKeyState[KEY_INPUT_UP] != 0)				//��Ɉړ�
			{
				if (UFO1.Y - UFO1.MoveSpeed > 0)	//�����̏�̈ʒu���A��ʂ̈�ԏ�̈ʒu�����傫���Ƃ�
				{
					UFO1.Y -= UFO1.MoveSpeed;
				}
			}
			else if (AllKeyState[KEY_INPUT_DOWN] != 0)		//���Ɉړ�
			{
				if (UFO1.Y + UFO1.Height + UFO1.MoveSpeed < GAME_HEIGHT)	//�����̉��̈ʒu���A��ʂ̈�ԉ��̈ʒu�����������Ƃ�
				{
					UFO1.Y += UFO1.MoveSpeed;
				}
			}
			if (AllKeyState[KEY_INPUT_LEFT] != 0)			//���Ɉړ�
			{
				if (UFO1.X - UFO1.MoveSpeed > 0)			//�����̍��̈ʒu���A��ʂ̈�ԍ��̈ʒu�����傫���Ƃ�
				{
					UFO1.X -= UFO1.MoveSpeed;
				}
			}
			else if (AllKeyState[KEY_INPUT_RIGHT] != 0)		//�E�Ɉړ�
			{
				if (UFO1.X + UFO1.Width + UFO1.MoveSpeed < GAME_WIDTH)		//�����̉E�̈ʒu���A��ʂ̈�ԉE�̈ʒu�����������Ƃ�
				{
					UFO1.X += UFO1.MoveSpeed;
				}

			}

			//�w�i�̕`��
			DrawGraph(BackGround.X, BackGround.Y, BackGround.Handle, TRUE);

			if (UFO1.IsView == TRUE)
			{
				DrawGraph(UFO1.X, UFO1.Y, UFO1.Handle, TRUE);//UFO��`��
			}


			//�l�p�`�̒���h��Ԃ��Ȃ��ŕ`��

			DrawBox(UFO1.X, UFO1.Y, UFO1.X + UFO1.Width, UFO1.Y + UFO1.Height, GetColor(0, 255, 255), FALSE);


			break;//�v���C��ʂ̏��������܂�
		case (int)GAME_SCENE_END://�G���h��ʂ̏�����������

			MY_GAME_END();

			break;//�G���h��ʂ̏��������܂�

		default:

			break;
		}

		MY_FPS_DRAW();		//FPS�̏���[�`��]

		ScreenFlip();		//���j�^�̃��t���b�V�����[�g�̑����ŗ���ʂ��ĕ`��

		MY_FPS_WAIT();		//FPS�̏���[�҂�]

	}

	DeleteFontToHandle(HFont_tanu_32);	//�t�H���g�̃n���h�����폜

	DeleteGraph(BackGround.Handle);		//�摜�̃n���h�����폜
	DeleteGraph(UFO1.Handle);			//�摜�̃n���h�����폜
	//DeleteGraph(CRAB1.Handle);			//�摜�̃n���h�����폜

	DxLib_End();		//�c�w���C�u�����g�p�̏I������

	return 0;

}

//########## �^�C�g����ʂ̊֐� ##########
VOID MY_GAME_TITLE(VOID)
{
	if (AllKeyState[KEY_INPUT_RETURN] != 0)//�G���^�[�L�[���������Ƃ�
	{
		GameSceneNow = (int)GAME_SCENE_PLAY;//�v���C��ʂɂ���
	}

	//�w�i�̕`��
	DrawGraph(BackGround.X, BackGround.Y, BackGround.Handle, TRUE);

	//�\�����镶����
	char title1[64] = "��~��`��~��";
	//�f�t�H���g�̃t�H���g��ύX����
	ChangeFont("MS �S�V�b�N", DX_CHARSET_DEFAULT);
	//�f�t�H���g�̃t�H���g�T�C�Y��ς���
	SetFontSize(64);
	//�t�H���g�����ꂢ�ɂ݂���
	ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE);
	//�f�t�H���g�̃t�H���g�̉������擾
	int TitleStringWidth1 = GetDrawFormatStringWidth(title1);
	//�f�t�H���g�̃t�H���g�̍������擾
	int TitleStringHeight1 = GetFontSize();
	//�f�t�H���g�̃t�H���g�ŕ`��
	DrawFormatString(GAME_WIDTH / 2 - TitleStringWidth1 / 2, GAME_HEIGHT / 2, GetColor(255, 255, 255), title1);

	//�\�����镶����
	char title2[64] = " GAME START";
	//�f�t�H���g�̃t�H���g��ύX����
	ChangeFont("MS ����", DX_CHARSET_DEFAULT);
	//�f�t�H���g�̃t�H���g�T�C�Y��ς���
	SetFontSize(48);
	//�t�H���g�����ꂢ�ɂ݂���
	ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE);
	//�f�t�H���g�̃t�H���g�̉������擾
	int TitleStringWidth2 = GetDrawFormatStringWidth(title2);
	//�f�t�H���g�̃t�H���g�̍������擾
	int TitleStringHeight2 = GetFontSize();
	//�f�t�H���g�̃t�H���g�ŕ`��
	DrawFormatString(GAME_WIDTH / 2 - TitleStringWidth2 / 2, GAME_HEIGHT / 2 + TitleStringHeight1, GetColor(255, 255, 255), title2);

	return;

}

//########## �G���h��ʂ̊֐� ##########
VOID MY_GAME_END(VOID)
{
	char EndWin[64] = "GAME OVER";

	//�f�t�H���g�̃t�H���g��ύX����
	ChangeFont("MS �S�V�b�N", DX_CHARSET_DEFAULT);
	//�f�t�H���g�̃t�H���g�T�C�Y��ς���
	SetFontSize(100);
	//�t�H���g�����ꂢ�ɂ݂���
	ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE);
	//�^�C�g�������P�̉������擾
	int EmdStringWidth1 = GetDrawFormatStringWidth(EndWin);
	//�^�C�g�������P�̍������擾
	int EndStringHeight1 = GetFontSize();

	//�w�i�̕`��
	DrawGraph(BackGround.X, BackGround.Y, BackGround.Handle, TRUE);
	DrawFormatString(GAME_WIDTH / 2 - EmdStringWidth1 / 2, GAME_HEIGHT / 2, GetColor(255, 255, 255), "GAME OVER");

	if (AllKeyState[KEY_INPUT_SPACE] != 0)
	{
		GameSceneNow = (int)GAME_SCENE_TITLE;
	}



	return;
}
//########## �v���C��ʂ̏���`�悷��֐� ##########
VOID MY_DRAW_PLAY_INFO(VOID)
{
	if (UFO1.IsView == TRUE)
	{
		DrawGraph(UFO1.X, UFO1.Y, UFO1.Handle, TRUE);//UFO��`��
	}

	//�l�p�`�̒���h��Ԃ��Ȃ��ŕ`��

	DrawBox(UFO1.X, UFO1.Y, UFO1.X + UFO1.Width, UFO1.Y + UFO1.Height, GetColor(0, 255, 255), FALSE);
	//DrawBox(CRAB1.X, CRAB1.Y, CRAB1.X + CRAB1.Width, CRAB1.Y + CRAB1.Height, GetColor(0, 255, 255), FALSE);



	return;
}



//########## �L�[�̓��͏�Ԃ��X�V����֐� ##########
VOID MY_ALL_KEYDOWN_UPDATE(VOID)
{
	char TempKey[256];			//�ꎞ�I�ɁA���݂̃L�[�̓��͏�Ԃ��i�[����

	GetHitKeyStateAll(TempKey); // �S�ẴL�[�̓��͏�Ԃ𓾂�

	for (int i = 0; i < 256; i++)
	{
		if (TempKey[i] != 0)	//������Ă���L�[�̃L�[�R�[�h�������Ă���Ƃ�
		{
			AllKeyState[i]++;	//������Ă���
		}
		else
		{
			AllKeyState[i] = 0;	//������Ă��Ȃ�
		}
	}
	return;
}

//########## FPS�l���v���A�X�V����֐� ##########
VOID MY_FPS_UPDATE(VOID)
{
	if (CountFps == 0) //1�t���[���ڂȂ玞�����L��
	{
		StartTimeFps = GetNowCount();
	}

	if (CountFps == SampleNumFps) //60�t���[���ڂȂ畽�ς��v�Z
	{
		int now = GetNowCount();
		CalcFps = 1000.f / ((now - StartTimeFps) / (float)SampleNumFps);
		CountFps = 0;
		StartTimeFps = now;
	}
	CountFps++;
	return;
}

//########## FPS�l��`�悷��֐� ##########
VOID MY_FPS_DRAW(VOID)
{

	//�t�H���g�n���h�����g�p���ĕ������`��
	DrawFormatStringToHandle(0, 0, GetColor(255, 255, 255), HFont_tanu_32, "FPS:%.1f", CalcFps);

	return;
}

//########## FPS�l���v�����A�҂֐� ##########
VOID MY_FPS_WAIT(VOID)
{
	int resultTime = GetNowCount() - StartTimeFps;					//������������
	int waitTime = CountFps * 1000 / GAME_FPS_SPEED - resultTime;	//�҂ׂ�����

	if (waitTime > 0)	//�������镪�A�ҋ@
	{
		Sleep(waitTime);
	}
	return;
}

//########## �t�H���g��ǂݍ��ފ֐� ##########
//���@���Fconst char *�F�ǂݍ��ރt�H���g�̖��O
//���@���Fint *�F�t�H���g�̃n���h��
//���@���Fint�@�F�t�H���g�̑傫��
//���@���Fint�@�F�t�H���g�̑���
//���@���Fint�@�F�t�H���g�̃^�C�v
//�߂�l�F�Ȃ����ύX���߂�l�FBOOL�F�G���[���FFALSE
BOOL MY_FONT_CREATE(const char *name, int *f, int pt, int bold, int type)
{
	*f = CreateFontToHandle(name, pt, bold, type);	//�t�H���g�n���h���쐬
	if (*f == -1) { return FALSE; }					//�쐬���s

	return TRUE;
}

//########## �摜��ǂݍ��ސݒ������֐� ##########
//���@���F�摜�\���́@�F�ݒ肷��摜�\���̂̕ϐ�
//���@���Fint�@�F�摜�̉��̈ʒu
//���@���Fint�@�F�摜�̏c�̈ʒu
//���@���Fconst char *�F�ǂݍ��މ摜�̃t�@�C���p�X
//�߂�l�FBOOL�F�G���[���FFALSE
BOOL MY_GAZOU_LOAD(GAZOU *g, int x, int y, const char *path)
{
	wsprintf(g->FilePath, path);						//�t�@�C���p�X���R�s�[
	g->Handle = LoadGraph(g->FilePath);					//�摜���������ɓǂݍ��݁A�n���h�����擾

	if (g->Handle == -1) { return FALSE; }				//�摜�ǂݍ��݃G���[

	GetGraphSize(g->Handle, &g->Width, &g->Height);		//�摜�T�C�Y���擾
	g->X = x;
	g->Y = y;
	g->C_Width = g->Width / 2;							//�摜�̉��T�C�Y�̒��S���擾
	g->C_Height = g->Height / 2;						//�摜�̏c�T�C�Y�̒��S���擾

	g->MoveSpeed = 4;									//�ړ����x
	g->IsView = TRUE;

	return TRUE;
}