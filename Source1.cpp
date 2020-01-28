//########## ヘッダーファイル読み込み ##########
#include "DxLib.h"
#include <math.h>
//########## マクロ定義 ##########
#define GAME_WIDTH	640		//画面の横の大きさ
#define GAME_HEIGHT	640		//画面の縦の大きさ
#define GAME_COLOR	32		//画面のカラービット

#define GAME_WINDOW_NAME	"GAME TITLE"		//ウィンドウのタイトル
#define GAME_WINDOW_MODECHANGE	TRUE			//TRUE：ウィンドウモード / FALSE：フルスクリーン

#define SET_WINDOW_ST_MODE_DEFAULT			0	//デフォルト
#define SET_WINDOW_ST_MODE_TITLE_NONE		1	//タイトルバーなし
#define SET_WINDOW_ST_MODE_TITLE_FLAME_NONE	2	//タイトルバーとフレームなし
#define SET_WINDOW_ST_MODE_FLAME_NONE		3	//フレームなし

#define GAME_WINDOW_NAME	"迷宮 MIGONG"

#define GAME_FPS_SPEED					   60

#define GAME_BACKIMAGE_1		"BACKIMAGE\\sp1.jpg"				//背景画像
#define GAME_BACKIMAGE_2		"BACKIMAGE\\side07.jpg"				//背景画像
#define GAME_BACKIMAGE_3		"BACKIMAGE\\tuzhong.jpg"				//背景画像



#define GAME_MAP_1		"MAPIMAGE\\MapData1.png"	//マップ画像
#define GAME_MAP_CSV_1	"MAPIMAGE\\lan.csv"//マップのCSV
#define GAME_CHARA_1	"CHARAIMAGE\\333.png"//キャラの画像


#define GAME_MAP_BUN_YOKO_CNT	20		//マップの分割数(横)
#define GAME_MAP_BUN_TATE_CNT	20		//マップの分割数(縦)

#define GAME_MUSIC_BGM_1		"MUSIC\\BGM\\BGM1.mp3"				//BG'm
#define GAME_MUSIC_BGM_2		"MUSIC\\BGM\\BGM3.mp3"			//BGM
#define GAME_MUSIC_BGM_3		"MUSIC\\BGM\\BGM4.mp3"			//BGM

#define GAME_MAP_YOKO		40			//マップの数(横)
#define GAME_MAP_TATE		20			//マップの数(縦)

#define GAME_MAP_YOKO_SIZE	32			//マップ１つの大きさ(横)x
#define GAME_MAP_TATE_SIZE	32			//マップ１つの大きさ(縦)

#define GAME_CHARA_BUN_YOKO_CNT	12		//キャラの分割数(横)
#define GAME_CHARA_BUN_TATE_CNT	8		//キャラの分割数(縦)

#define GAME_CHARA_YOKO_SIZE	24		//キャラの大きさ(横)
#define GAME_CHARA_TATE_SIZE	32		//キャラの大きさ(縦)

#define GAME_CHARA_MOTION_NUM	12		//キャラの画像数

#define GAME_CHARA_KIND_YOKO	3		//キャラの横の種類
#define GAME_CHARA_KIND_TATE	4		//キャラの縦の種類

#define GAME_CHARA_SPEED		3		//キャラのスピード

#define GAME_MAP_NOTDOWN_KIND	8		//下に行けないマップの種類	
#define GAME_MAP_OKDOWN_KIND	2		//下に行けるマップの種類	

#define GAME_MAP_NOTUP_KIND		8		//上に行けないマップの種類
#define GAME_MAP_NOTLEFT_KIND	8		//左に行けないマップの種類
#define GAME_MAP_NOTRIGHT_KIND	8		//右に行けないマップの種類


//########## 列挙型 ##########
enum GAME_SCENE {
	GAME_SCENE_TITLE,//タイトル画面
	GAME_SCENE_TUZHONG,
	GAME_SCENE_PLAY,//プレイ画面
	GAME_SCENE_END//エンド画面
};

enum BACK_IMAGE {
	BACK_IMAGE_1,
	BACK_IMAGE_2,
	BACK_IMAGE_END		//背景の終了
};	//背景の列挙型

enum MAP_IMAGE {
	M_N = -1,	//MAP_NULLの意味
	M_B = 19,	//MAP_BLANKの意味
	M_G_T = 6,	//MAP_GROUND_TOPの意味
	M_G_N = 38,	//MAP_GROUND_NAKAの意味
	M_AM = 95,	//MAP_AMAZUNの意味
	M_END = 399	//マップの終了
};	//マップの列挙型

enum CHARA_IMAGE {
	CHARA_KIND_1 = 0,
	CHARA_KIND_2 = 3,
	CHARA_KIND_3 = 6,
	CHARA_KIND_4 = 9,
	CHARA_KIND_5 = 48,
	CHARA_KIND_6 = 51,
	CHARA_KIND_END = 95
};	//キャラの種類の列挙型

enum GAME_END_KIND {
	END_KIND_CONTINUE,	//ゲーム続行
	END_KIND_OVER,		//ゲームオーバー
	END_KIND_CLEAR		//ゲームクリア
};	//ゲーム終了の種類

//########## 構造体 ##########
struct STRUCT_GAZOU {
	int Handle;		//画像のハンドル
	char FilePath[128];//ファイルのパス
	int X;			//横の位置
	int Y;			//縦の位置
	int Width;		//横のサイズ
	int Height;		//縦のサイズ
	int C_Width;	//横の中心位置
	int C_Height;	//縦の中心位置
};

struct STRUCT_MAP
{
	char FilePath[128];		//ファイルのパス
	int Handle[GAME_MAP_BUN_YOKO_CNT * GAME_MAP_BUN_TATE_CNT];		//画像のハンドル
	int X[GAME_MAP_BUN_YOKO_CNT * GAME_MAP_BUN_TATE_CNT];			//横の位置
	int Y[GAME_MAP_BUN_YOKO_CNT * GAME_MAP_BUN_TATE_CNT];			//縦の位置
	int Width[GAME_MAP_BUN_YOKO_CNT * GAME_MAP_BUN_TATE_CNT];		//横のサイズ
	int Height[GAME_MAP_BUN_YOKO_CNT * GAME_MAP_BUN_TATE_CNT];		//縦のサイズ
	int C_Width[GAME_MAP_BUN_YOKO_CNT * GAME_MAP_BUN_TATE_CNT];		//横の中心位置
	int C_Height[GAME_MAP_BUN_YOKO_CNT * GAME_MAP_BUN_TATE_CNT];	//縦の中心位置

	BOOL charaStopFlag;				//キャラの移動制御フラグ
	BOOL GoalFlg;					//このマップをゴールしたか

	int GameEndKind;				//ゲーム終了の種類
	BOOL GoalEffect1;				//ゴールしたときの演出１
};	//MAP構造体

struct STRUCT_CHARACTOR
{
	char FilePath[128];						//ファイルのパス
	int Handle[GAME_CHARA_BUN_YOKO_CNT * GAME_CHARA_BUN_TATE_CNT];		//画像のハンドル
	int X[GAME_CHARA_BUN_YOKO_CNT * GAME_CHARA_BUN_TATE_CNT];			//横の位置
	int Y[GAME_CHARA_BUN_YOKO_CNT * GAME_CHARA_BUN_TATE_CNT];			//縦の位置
	int Width[GAME_CHARA_BUN_YOKO_CNT * GAME_CHARA_BUN_TATE_CNT];		//横のサイズ
	int Height[GAME_CHARA_BUN_YOKO_CNT * GAME_CHARA_BUN_TATE_CNT];		//縦のサイズ
	int C_Width[GAME_CHARA_BUN_YOKO_CNT * GAME_CHARA_BUN_TATE_CNT];		//横の中心位置
	int C_Height[GAME_CHARA_BUN_YOKO_CNT * GAME_CHARA_BUN_TATE_CNT];	//縦の中心位置
};	//CHARA構造体

struct STRUCT_PLAYER
{
	int Handle[GAME_CHARA_MOTION_NUM];	//画像のハンドル
	int X;								//横の位置
	int Y;								//縦の位置
	int Width;							//横のサイズ
	int Height;							//縦のサイズ
	int C_Width;						//横の中心位置
	int C_Height;						//縦の中心位置
	int NowHandleNum;					//現在の画像のハンドル
	int NowHandleCnt;					//現在のハンドルカウント
	int NowHandleCntMAX;				//現在のハンドルカウントMAX

	int Speed;							//速度
	int MoveDist;						//移動距離

	BOOL CanMoveUp;					//上に行けるか
	BOOL CanMoveDown;					//下に行けるか
	BOOL CanMoveLeft;					//左に行けるか
	BOOL CanMoveRight;					//右に行けるか

	int atariX;							//当たり判定のX位置
	int atariY;							//当たり判定のY位置
	int atariWidth;						//当たり判定の幅
	int atariHeight;					//当たり判定の高さ

	RECT atariRect;						//当たり判定の矩形領域
};	//PLAYER構造体

struct STRUCT_MUSIC
{
	int Handle;					//音のハンドル
	char FilePath[128];			//ファイルのパス
	int Playtype;				//音の再生方法
};	//音構造体

//########## 名前の再定義 ##########
typedef STRUCT_GAZOU GAZOU;
typedef STRUCT_MAP MAP;
typedef STRUCT_CHARACTOR CHARA;
typedef STRUCT_PLAYER PLAYER;
typedef STRUCT_MUSIC MUSIC;

//########## グローバル変数 ##########

//音を読み込む
MUSIC MUSIC_MY_BGM_1;	//BGM
MUSIC MUSIC_MY_BGM_2;	//BGM
MUSIC MUSIC_MY_BGM_3;	//BGM

//ウィンドウ関係
WNDPROC WndProc;						//ウィンドウプロシージャのアドレス
BOOL IsWM_CREATE = FALSE;				//WM_CREATEが正常に動作したか判断する

										//FPS関連
int StartTimeFps;						//測定開始時刻
int CountFps;							//カウンタ
float CalcFps;							//計算結果
int SampleNumFps = GAME_FPS_SPEED;		//平均を取るサンプル数

//キーボード関連
char AllKeyState[256];					//すべてのキーの状態が入る

//シーン関連
int GameSceneNow = (int)GAME_SCENE_TITLE;	//最初のゲーム画面をタイトルに設定

GAZOU	BackImage[5];			//背景の画像

int ScrollCntYoko = 0;			//スクロールカウンタ(横)
int ScrollCntTate = 0;			//スクロールカウンタ

int ScrollDistPlusYoko = 1;		//スクロールする距離(横)
int ScrollDistPlusTate = 1;		//スクロールする距離

MAP MapImage;		//マップの画像

int ScrollDistKeyPlusYoko = 2;	//矢印キーのスクロールする距離
int ScrollDistKeyPlusTate = 2;	//矢印キーのスクロールする距離

CHARA CharaImage;		//キャラの画像
PLAYER Myplayer;		//プレイヤー

//プレイヤーのイメージ画像の番号を設定する
int PlayerImageNum[GAME_CHARA_MOTION_NUM] =
										 {	00,01,01,
											12,13,14,
											24,25,26,
											36,37,38 };


int MapData[GAME_MAP_TATE][GAME_MAP_YOKO];//マップのデータ
int MapData_Init[GAME_MAP_TATE][GAME_MAP_YOKO];	//マップのデータ（初期化用）
FILE *fp_map_csv;//ファイルの管理番号(ポインタ≒ハンドル)

int MapNotDownKind[GAME_MAP_NOTDOWN_KIND] = { 20,9,10,37,38,67,87 ,108 };	//下に行けないマップの番号
int MapOKDownKind[GAME_MAP_OKDOWN_KIND] = { 19 };					//下に行けるマップの番号

int MapNotUpKind[GAME_MAP_NOTUP_KIND] = { 20,8,9,10,37,38,67,108 };		//上に行けないマップの番号
int MapNotLeftKind[GAME_MAP_NOTLEFT_KIND] = { 20,8,9,10,37,38,67,108 };	//左に行けないマップの番号
int MapNotRightKind[GAME_MAP_NOTRIGHT_KIND] = { 20,8,9,10,37,38,67 ,108 };	//右に行けないマップの番号

RECT rectMap_DownNG[GAME_MAP_TATE][GAME_MAP_YOKO];					//マップの当たり判定(下に行けない)		
RECT rectMap_DownNG_First[GAME_MAP_TATE][GAME_MAP_YOKO];			//マップの当たり判定(下に行けない)(初期位置)		

RECT rectMap_DownOK[GAME_MAP_TATE][GAME_MAP_YOKO];					//マップの当たり判定(下に行ける)		
RECT rectMap_DownOK_First[GAME_MAP_TATE][GAME_MAP_YOKO];			//マップの当たり判定(下に行ける)(初期位置)	

RECT rectMap_LeftNG[GAME_MAP_TATE][GAME_MAP_YOKO];					//マップの当たり判定(左に行けない)		
RECT rectMap_LeftNG_First[GAME_MAP_TATE][GAME_MAP_YOKO];			//マップの当たり判定(左に行けない)(初期位置)

RECT rectMap_RightNG[GAME_MAP_TATE][GAME_MAP_YOKO];					//マップの当たり判定(右に行けない)		
RECT rectMap_RightNG_First[GAME_MAP_TATE][GAME_MAP_YOKO];			//マップの当たり判定(右に行けない)(初期位置)	

RECT rectMap_UpNG[GAME_MAP_TATE][GAME_MAP_YOKO];					//マップの当たり判定(上に行けない)		
RECT rectMap_UpNG_First[GAME_MAP_TATE][GAME_MAP_YOKO];				//マップの当たり判定(上に行けない)(初期位置)	

BOOL IsActiveCheck = FALSE;			//画面のアクティブチェック有効化

int StopActiveStartTime = 0;	//非アクティブ化の開始時間
int StopActiveStopTime = 0;		//非アクティブ化の終了時間
int StopActiveTotalTime = 0;	//非アクティブ化の経過時間	
//########## プロトタイプ宣言 ##########
//LRESULT CALLBACK MY_WNDPROC(HWND, UINT, WPARAM, LPARAM);		//自作ウィンドウプロシージャ

VOID MY_FPS_UPDATE(VOID);//FPS値を計測、更新する関数
VOID MY_FPS_DRAW(VOID);	//FPS値を描画する関数
VOID MY_FPS_WAIT(VOID);	//FPS値を計測し、待つ関数

VOID MY_ALL_KEYDOWN_UPDATE(VOID);//キーの入力状態を更新する関数

VOID MY_GAME_TITLE(VOID);//タイトル画面の関数
VOID MY_GAME_TUZHONG(VOID);
VOID MY_GAME_PLAY(VOID);//プレイ画面の関数
VOID MY_GAME_END(VOID);	//エンド画面の関数

BOOL MY_GAZOU_LOAD(GAZOU *, int, int, const char *);	//画像を読み込む設定をする関数

BOOL MY_PLAY_INIT(VOID);			//プレイ画面初期化関数
VOID MY_PLAY_BACKIMAGE_DRAW(VOID);	//背景を表示する関数
VOID MY_PLAY_BACKIMAGE1_DRAW(VOID);	//背景を表示する関数
VOID MY_PLAY_BACKIMAGE2_DRAW(VOID);	//背景を表示する関数

VOID MY_PLAY_SCROLL(VOID);			//ゲーム画面のスクロールを行う関数

BOOL MY_MAP_READ_CSV_NUM(FILE *, const char *);//ゲームマップのCSVを読み込む関数
BOOL MY_MAP_LOAD_BUNKATSU(MAP *, int, int, int, int, int, const char *);
BOOL MY_CHARA_LOAD_BUNKATSU(CHARA*, int, int, int, int, int, const char *);	//CHARAを分割して読み込む設定をする関数

BOOL MY_MUSIC_LOAD(MUSIC *, const char *);	//音を読み込む設定をする関数

BOOL MY_INIT_PLAYER(PLAYER *, CHARA, int *, int, int, int);					//プレイヤーを初期化する関数

VOID MY_PLAY_PLAYER_DRAW(VOID);						//プレイヤーを表示する関数
VOID MY_PLAY_PLAYER_OPERATION(VOID);				//プレイヤーを操作する関数
VOID MY_PLAY_MAP_DRAW(VOID);						//マップを表示する関数

BOOL MY_PLAY_CHECK_GAME_END(VOID);		//ゲームエンドか判定する関数

VOID MY_DRAW_STRING_CENTER_CENTER(char[][128], int, char *, int);		//画面中央に文字を描画する関数
VOID MY_DRAW_SET_DEFAULT_FONT(BOOL);									//文字をデフォルトフォントに設定する関数

VOID MY_BG_IMAGE_INIT(VOID);			//背景初期化関数

VOID MY_SET_PLAYER_ATARI(PLAYER *);			//プレイヤーの当たり判定の領域を設定する関数

BOOL MY_CHECK_RECT_ATARI(RECT, RECT);		// 領域の当たり判定をする関数

BOOL MY_CHECK_RECT_ATARI_CHARA_MAP(RECT, RECT[GAME_MAP_TATE][GAME_MAP_YOKO]);	//マップとの当たり判定をする関数

//########## プログラムで最初に実行される関数 ##########
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(GAME_WINDOW_MODECHANGE);//ウィンドウモードに設定
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);//指定の数値で画面を表示する

	SetWindowStyleMode(SET_WINDOW_ST_MODE_DEFAULT);			//タイトルバー

	SetMainWindowText(TEXT(GAME_WINDOW_NAME));//タイトルの文字

	if (DxLib_Init() == -1) { return -1; }//ＤＸライブラリ初期化処理

	SetDrawScreen(DX_SCREEN_BACK);//Draw系関数は裏画面に描画

	if (MY_GAZOU_LOAD(&BackImage[0], 0, 0, GAME_BACKIMAGE_1) == FALSE) { MessageBox(NULL, GAME_BACKIMAGE_1, "NotFound", MB_OK); return -1; }	//背景を読み込む①
	if (MY_GAZOU_LOAD(&BackImage[1], 0, 0, GAME_BACKIMAGE_2) == FALSE) { MessageBox(NULL, GAME_BACKIMAGE_2, "NotFound", MB_OK); return -1; }	//背景を読み込む
	if (MY_GAZOU_LOAD(&BackImage[2], 0, 0, GAME_BACKIMAGE_3) == FALSE) { MessageBox(NULL, GAME_BACKIMAGE_3, "NotFound", MB_OK); return -1; }	//背景を読み込む
	MY_BG_IMAGE_INIT();		//背景位置を初期化

	//画像の分割数をこっそり修正。
	if (MY_MAP_LOAD_BUNKATSU(&MapImage, GAME_MAP_BUN_YOKO_CNT * GAME_MAP_BUN_TATE_CNT, GAME_MAP_BUN_TATE_CNT, GAME_MAP_BUN_YOKO_CNT, 32, 32, GAME_MAP_1) == FALSE) { MessageBox(NULL, GAME_MAP_1, "NotFound", MB_OK); return -1; }	//MAPを読み込む

	if (MY_CHARA_LOAD_BUNKATSU(&CharaImage, GAME_CHARA_BUN_YOKO_CNT * GAME_CHARA_BUN_TATE_CNT, GAME_CHARA_BUN_YOKO_CNT, GAME_CHARA_BUN_TATE_CNT, GAME_CHARA_YOKO_SIZE, GAME_CHARA_TATE_SIZE, GAME_CHARA_1) == FALSE) { MessageBox(NULL, GAME_CHARA_1, "NotFound", MB_OK); return -1; }	//CHARAを読み込む

	if (MY_MAP_READ_CSV_NUM(fp_map_csv, GAME_MAP_CSV_1) == FALSE) { MessageBox(NULL, GAME_MAP_CSV_1, "NotFound", MB_OK); return -1; }	//CSVを読み込む

	//音を読み込む
	MY_MUSIC_LOAD(&MUSIC_MY_BGM_1, GAME_MUSIC_BGM_1); 
	MY_MUSIC_LOAD(&MUSIC_MY_BGM_2, GAME_MUSIC_BGM_2);
	MY_MUSIC_LOAD(&MUSIC_MY_BGM_3, GAME_MUSIC_BGM_3);

	//画面のアクティブチェック有効化
	IsActiveCheck = TRUE;

	//無限ループ
	while (TRUE)
	{
		if (ProcessMessage() != 0) { break; }//メッセージ処理の結果がエラーのとき、強制終了

		if (ClearDrawScreen() != 0) { break; }//画面を消去できなかったとき、強制終了

		MY_ALL_KEYDOWN_UPDATE();//キーの状態を取得

		//シーン選択
		switch (GameSceneNow)
		{

		case (int)GAME_SCENE_TITLE:	//タイトル画面の処理ここから

			MY_GAME_TITLE();//タイトル画面の処理

			break;//タイトル画面の処理ここまで

		case (int)GAME_SCENE_TUZHONG://プレイ画面の処理ここから

			MY_GAME_TUZHONG();//プレイ画面の処理

			break;//プレイ画面の処理ここまで

		case (int)GAME_SCENE_PLAY://プレイ画面の処理ここから

			MY_GAME_PLAY();//プレイ画面の処理

			break;//プレイ画面の処理ここまで

		case (int)GAME_SCENE_END://エンド画面の処理ここから

			MY_GAME_END();//エンド画面の処理

			break;//エンド画面の処理ここまで

		default:

			break;
		}

		MY_FPS_UPDATE();//FPSの処理[更新]

		MY_FPS_DRAW();//FPSの処理[描画]

		ScreenFlip();//モニタのリフレッシュレートの速さで裏画面を再描画

		MY_FPS_WAIT();//FPSの処理[待つ]
	}

	DeleteGraph(BackImage[0].Handle);		//背景のハンドルを削除
	DeleteGraph(BackImage[1].Handle);		//背景のハンドルを削除
	DeleteGraph(BackImage[2].Handle);		//背景のハンドルを削除



	DeleteMusicMem(MUSIC_MY_BGM_1.Handle);		//音のハンドルを削除
	DeleteMusicMem(MUSIC_MY_BGM_2.Handle);		//音のハンドルを削除
	DeleteMusicMem(MUSIC_MY_BGM_3.Handle);		//音のハンドルを削除

	for (int mapCnt = 0; mapCnt < GAME_MAP_BUN_YOKO_CNT * GAME_MAP_BUN_TATE_CNT; mapCnt++)
	{
		DeleteGraph(MapImage.Handle[mapCnt]);	//マップのハンドルを削除
	}

	for (int charaCnt = 0; charaCnt < GAME_CHARA_BUN_YOKO_CNT* GAME_CHARA_BUN_TATE_CNT; charaCnt++)
	{
		DeleteGraph(MapImage.Handle[charaCnt]);	//キャラのハンドルを削除
	}

	DxLib_End();//ＤＸライブラリ使用の終了処理

	return 0;
}

//########## FPS値を計測、更新する関数 ##########
VOID MY_FPS_UPDATE(VOID)
{
	if (CountFps == 0)//1フレーム目なら時刻を記憶
	{
		StartTimeFps = GetNowCount();
	}

	if (CountFps == SampleNumFps) //60フレーム目なら平均を計算
	{
		int now = GetNowCount();
		CalcFps = 1000.f / ((now - StartTimeFps) / (float)SampleNumFps);
		CountFps = 0;
		StartTimeFps = now;
	}
	CountFps++;
	return;
}

//########## FPS値を描画する関数 ##########
VOID MY_FPS_DRAW(VOID)
{
	//文字列を描画
	DrawFormatString(0, GAME_HEIGHT - 20, GetColor(255, 255, 255), "FPS:%.1f", CalcFps);
	return;
}

//########## FPS値を計測し、待つ関数 ##########
VOID MY_FPS_WAIT(VOID)
{
	int resultTime = GetNowCount() - StartTimeFps;//かかった時間
	int waitTime = CountFps * 1000 / GAME_FPS_SPEED - resultTime;//待つべき時間

	if (waitTime > 0)//指定のFPS値よりも早い場合
	{
		Sleep(waitTime);//待つ
	}
	return;
}

//########## キーの入力状態を更新する関数 ##########
VOID MY_ALL_KEYDOWN_UPDATE(VOID)
{
	char TempKey[256];			//一時的に、現在のキーの入力状態を格納する

	GetHitKeyStateAll(TempKey); // 全てのキーの入力状態を得る

	for (int i = 0; i < 256; i++)
	{
		if (TempKey[i] != 0)	//押されているキーのキーコードを押しているとき
		{
			AllKeyState[i]++;	//押されている
		}
		else
		{
			AllKeyState[i] = 0;	//押されていない
		}
	}
	return;
}

//########## タイトル画面の関数 ##########
VOID MY_GAME_TITLE(VOID)
{

	if (CheckSoundMem(MUSIC_MY_BGM_1.Handle) == 0)
	{
		ChangeVolumeSoundMem(255 * 50 / 100, MUSIC_MY_BGM_1.Handle);	//BGMの音量を50％にする
		PlaySoundMem(MUSIC_MY_BGM_1.Handle, DX_PLAYTYPE_LOOP);			//BGMを流す
	}
	if (AllKeyState[KEY_INPUT_RETURN] != 0)	//エンターキーが押されていた時
	{

		if (MY_PLAY_INIT() == TRUE)		//プレイ画面初期化
		{

			for (int tate = 0; tate < GAME_MAP_TATE; tate++)
			{
				for (int yoko = 0; yoko < GAME_MAP_YOKO; yoko++)
				{
					MapData[tate][yoko] = MapData_Init[tate][yoko];	//マップをもとに戻す
				}
			}

			GameSceneNow = (int)GAME_SCENE_TUZHONG;	//シーンを表示画面にする

		}
	}

	MY_PLAY_BACKIMAGE1_DRAW();	//背景を描画

	return;
}

VOID MY_GAME_TUZHONG(VOID)
{

	MY_PLAY_BACKIMAGE2_DRAW();	//背景を描画
	//DrawString(0, 0, "", GetColor(255, 255, 255));
	DrawString(0, 30, "ゲーム説明：", GetColor(255,89,38));
	DrawString(20, 60, "1.十字キーでキャラクターを移動しよう！", GetColor(0,0,0));
	DrawString(20, 90, "2.迷宮「MI GONG」を探索して、青い出口を探せ！", GetColor(0,0,0));
	DrawString(20, 120, "3.逃出成功でき、ゲームクリア！！", GetColor(255, 89, 38));
	DrawString(20, 150, "4.もしプレイする途中でクリア条件が忘れたら、\nバックスペースキーを押して、ゲーム説明画面に戻ろう!", GetColor(0,0,0));


	DrawString(0, 240, "スペースキーを押して始めよう!", GetColor(0,0,0));
	if (AllKeyState[KEY_INPUT_SPACE] != 0)	//スペースキーが押されていた時
	{
			StopSoundMem(MUSIC_MY_BGM_1.Handle);	//BGMを止める
			GameSceneNow = (int)GAME_SCENE_PLAY;	//シーンを表示画面にする	
	}

}

//########## プレイ画面の関数 ##########
VOID MY_GAME_PLAY(VOID)
{

	if (AllKeyState[KEY_INPUT_BACK] != 0)	//バックスペースキーが押されていた時
	{
		GameSceneNow = (int)GAME_SCENE_TUZHONG;	//シーンをタイトル画面にする
	}

	//BGMが流れていないとき
	if (CheckSoundMem(MUSIC_MY_BGM_2.Handle) == 0)
	{
		ChangeVolumeSoundMem(255 * 50 / 100, MUSIC_MY_BGM_2.Handle);	//BGMの音量を50％にする
		PlaySoundMem(MUSIC_MY_BGM_2.Handle, DX_PLAYTYPE_LOOP);			//BGMを流す
	}
	
	if (AllKeyState[KEY_INPUT_LEFT] != 0)	//左矢印キーが押されていた時
	{
		if (Myplayer.CanMoveLeft == TRUE)	//プレイヤーが左に動けるとき
		{
			if (MapImage.charaStopFlag == TRUE)	//プレイヤーを左右動かせないならば
			{
				if (ScrollCntYoko > 0)			//マイナスのスクロールをしない
				{
					ScrollCntYoko -= Myplayer.Speed;	//画面を左にスクロール
				}
			}
		}
	}

	if (AllKeyState[KEY_INPUT_RIGHT] != 0)	//右矢印キーが押されていた時
	{
		if (Myplayer.CanMoveRight == TRUE)	//プレイヤーが右に動けるとき
		{
			if (MapImage.charaStopFlag == TRUE)	//プレイヤーを左右動かせないならば
			{
				if (ScrollCntYoko < GAME_MAP_YOKO_SIZE * GAME_MAP_YOKO)	//画面外へスクロールしない
				{
					ScrollCntYoko += Myplayer.Speed;	//画面を右にスクロール
				}
			}
		}
	}

	if (MY_PLAY_CHECK_GAME_END() == TRUE)	//ゲームクリアか判定
	{

		StopSoundMem(MUSIC_MY_BGM_2.Handle);	//BGMを止める

		GameSceneNow = (int)GAME_SCENE_END;	//シーンをエンド画面にする
	}
	else
	{
		MY_PLAY_PLAYER_OPERATION();	//プレイヤーの操作
	}

	MY_PLAY_BACKIMAGE_DRAW();//背景を描画

	MY_PLAY_MAP_DRAW();//マップを描画

	MY_PLAY_PLAYER_DRAW();//プレイヤーを描画

	DrawString(0, 0, "バックスペースキーを押して、説明画面に戻る", GetColor(255, 255, 255));

	return;
}

//########## ゲームエンドか判定する関数 ##########
BOOL MY_PLAY_CHECK_GAME_END(VOID)
{

	//プレイヤーの位置は、プレイヤーの中心
		int PlayerToMapNumY = Myplayer.Y / GAME_MAP_TATE_SIZE;								//プレイヤーのY位置を計算
		int PlayerToMapNumX = (Myplayer.MoveDist + Myplayer.C_Width) / GAME_MAP_TATE_SIZE;	//プレイヤーのX位置を計算

	if (Myplayer.Y > GAME_HEIGHT)
	{
			MapImage.GameEndKind = (int)END_KIND_CLEAR;		//ゲームオーバー

		return TRUE;
	}

	return FALSE;	//ゲーム続行
}

//########## 文字をデフォルトフォントに設定する関数 ##########
//引　数：BOOL：アンチエイリアスをする
VOID MY_DRAW_SET_DEFAULT_FONT(BOOL anti)
{
	//デフォルトは以下のフォントとサイズであると、設定する
	ChangeFont("MS ゴシック", DX_CHARSET_DEFAULT);				//デフォルトのフォントを変更する
	SetFontSize(16);											//デフォルトのフォントサイズを変える

	if (anti)
	{
		ChangeFontType(DX_FONTTYPE_ANTIALIASING);					//フォントをきれいにみせる
	}
	return;
}

//########## エンド画面の関数 ##########
VOID MY_GAME_END(VOID)
{

	BOOL GoalEffect1DownFlg = FALSE;

	if (MapImage.GameEndKind == (int)END_KIND_CLEAR)	//ゲームクリアのとき
	{

		if (CheckSoundMem(MUSIC_MY_BGM_3.Handle) == 0)
		{
			ChangeVolumeSoundMem(255 * 50 / 100, MUSIC_MY_BGM_3.Handle);	//BGMの音量を50％にする
			PlaySoundMem(MUSIC_MY_BGM_3.Handle, DX_PLAYTYPE_LOOP);			//BGMを流す
		}

		MY_PLAY_BACKIMAGE_DRAW();//背景を描画

		MY_PLAY_MAP_DRAW();//マップを描画

		MY_PLAY_PLAYER_DRAW();//プレイヤーを描画
		if (MapImage.GoalEffect1 == FALSE)	//ゴールの演出をする
		{
			//プレイヤーの位置がマップ配列のどこにいるか変換
			int PlayerToMapNumY = Myplayer.Y / GAME_MAP_TATE_SIZE;
			int PlayerToMapNumX = (Myplayer.MoveDist + Myplayer.C_Width) / GAME_MAP_TATE_SIZE;

			//プレイヤーが下に行けないとき
			for (int NotD_Cnt = 0; NotD_Cnt < GAME_MAP_NOTDOWN_KIND; NotD_Cnt++)
			{
				//プレイヤーの１コ下のマップをチェックする
				if (Myplayer.Y >= 0)	//プレイヤーが画面内にいるとき
				{
					if (MapData[PlayerToMapNumY + 1][PlayerToMapNumX] == MapNotDownKind[NotD_Cnt])	//プレイヤーが下に行けないとき
					{
						MapImage.GoalEffect1 = TRUE;	//プレイヤーが下に行けなくなったら、演出終了
						break;
					}
					else if (MapData[PlayerToMapNumY + 1][PlayerToMapNumX] != MapNotDownKind[NotD_Cnt])	//プレイヤーが下に行けるとき
					{
						if (GoalEffect1DownFlg == FALSE)
						{
							Myplayer.Y++;			//プレイヤーを下に移動させる演出
							GoalEffect1DownFlg = TRUE;
						}
					}
				}
			}
		}

		if (AllKeyState[KEY_INPUT_BACK] != 0)//バックスペースーキーが押されていた時
		{
			StopSoundMem(MUSIC_MY_BGM_3.Handle);	//BGMを止める
			GameSceneNow = (int)GAME_SCENE_TITLE;//シーンをtitle画面にする
		}

	}

	if (MapImage.GameEndKind == (int)END_KIND_CLEAR)	//ゲームクリアのとき
	{
		char StrGameClear[2][128] = { "GAME CLEAR","逃出成功！" };
		char StrFontClear[128] = { "MS ゴシック" };	//大文字半角「MS」、半角「空白」、全角「ゴシック」

		MY_DRAW_STRING_CENTER_CENTER(&StrGameClear[0], 2, StrFontClear, 40);	//画面中央に描画

	}

	DrawString(0, 0, "　バックスペースキーを押して,タイトル画面に戻る　", GetColor(255, 255, 255));

	return;
}

//########## 画面中央に文字を描画する関数 ##########
//引　数：char [][]：表示する文字列の先頭アドレス
//引　数：int　 　 ：表示する行数
//引　数：char *　 ：フォントの名前
//引　数：int　 　 ：文字の大きさ
//戻り値：なし
VOID MY_DRAW_STRING_CENTER_CENTER(char str[][128], int row, char *fontname, int size)
{
	ChangeFont(fontname, DX_CHARSET_DEFAULT);					//デフォルトのフォントを変更する
	SetFontSize(size);											//デフォルトのフォントサイズを変える
	ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE);				//フォントをきれいにみせる

	int StrHeightSum = 0;
	for (int sum = 0; sum < row; sum++)	//行全体の高さを集計
	{
		StrHeightSum += GetFontSize();	//デフォルトのフォントの高さを取得
	}

	for (int rCnt = 0; rCnt < row; rCnt++)	//フォントを描画
	{
		int StrWidth = GetDrawFormatStringWidth(&str[rCnt][0]);				//デフォルトのフォントの横幅を取得
		int StrHeight = GetFontSize();

		DrawFormatString(
			GAME_WIDTH / 2 - StrWidth / 2,
			GAME_HEIGHT / 2 - StrHeightSum + StrHeight * rCnt,	//画面の中心　-　行全体の文字の高さ　+　１行の高さ
			GetColor(255, 255, 255), &str[rCnt][0]);	//デフォルトのフォントで描画

	}

	MY_DRAW_SET_DEFAULT_FONT(TRUE);		//デフォルトフォントに設定する

	return;
}

//########## 初期化関数 ##########
BOOL MY_PLAY_INIT(VOID)
{
	if (MY_INIT_PLAYER(&Myplayer, CharaImage, &PlayerImageNum[0], GAME_MAP_YOKO_SIZE * 0, GAME_MAP_TATE_SIZE * 0, GAME_CHARA_SPEED) == FALSE) { MessageBox(NULL, "CHARA_INIT", "NotFound", MB_OK); return FALSE; }

	Myplayer.X = 32; //プレイヤー初始位置
	Myplayer.Y = 32; //プレイヤー初始位置

	MapImage.GoalFlg = FALSE;	//ゴール状態を初期化

	MapImage.GameEndKind = (int)END_KIND_CONTINUE;		//ゲーム続行

	MapImage.GoalEffect1 = FALSE;		//ゴール効果OFF

	MY_DRAW_SET_DEFAULT_FONT(TRUE);	//デフォルトフォントに設定する

	MY_BG_IMAGE_INIT();	//背景の位置を初期化

	ScrollCntYoko = 0;		//スクロール量を初期化

	return TRUE;
}

//########## 背景の初期化関数 ##########
VOID MY_BG_IMAGE_INIT(VOID)
{
	//背景の位置
	BackImage[0].X = 0;
	BackImage[1].X = 0;
	BackImage[2].X = 0;

	return;
}

//########## 画像を読み込む設定をする関数 ##########
//引　数：画像構造体　：設定する画像構造体の変数
//引　数：int　：画像の横の位置
//引　数：int　：画像の縦の位置
//引　数：const char *：読み込む画像のファイルパス
//戻り値：BOOL：エラー時：FALSE
BOOL MY_GAZOU_LOAD(GAZOU *g, int x, int y, const char *path)
{
	wsprintf(g->FilePath, path);						//ファイルパスをコピー
	g->Handle = LoadGraph(g->FilePath);					//画像をメモリに読み込み、ハンドルを取得

	if (g->Handle == -1) { return FALSE; }				//画像読み込みエラー

	GetGraphSize(g->Handle, &g->Width, &g->Height);		//画像サイズを取得
	g->X = x;
	g->Y = y;
	g->C_Width = g->Width / 2;							//画像の横サイズの中心を取得
	g->C_Height = g->Height / 2;						//画像の縦サイズの中心を取得

	return TRUE;
}

//########## MAPを分割して読み込む設定をする関数 ##########
//引　数：MAP構造体　：設定する画像構造体(分割)の変数
//引　数：int　：画像の分割数
//引　数：int　：画像の横の分割数
//引　数：int　：画像の縦の分割数
//引　数：int　：画像の横の分割サイズ
//引　数：int　：画像の縦の分割サイズ
//引　数：const char *：読み込む画像のファイルパス
//戻り値：BOOL：エラー時：FALSE
BOOL MY_MAP_LOAD_BUNKATSU(MAP *m, int bun_num, int bun_x_num, int bun_y_num, int bun_width, int bun_height, const char *path)
{
	int ret = 0;
	wsprintf(m->FilePath, path);//ファイルパスをコピー

	//画像をメモリに分割して読み込み、ハンドルを取得
	ret = LoadDivGraph(m->FilePath, bun_num, bun_x_num, bun_y_num, bun_width, bun_height, m->Handle);

	if (ret == -1) { return FALSE; }//画像読み込みエラー

	for (int cnt = 0; cnt < GAME_MAP_BUN_YOKO_CNT*GAME_MAP_BUN_TATE_CNT; cnt++)
	{
		//画像サイズを取得
		GetGraphSize(
			m->Handle[cnt],//ハンドルから、画像の幅と高さを取得して・・・
			&m->Width[cnt],//MAP構造体の幅　に、画像の幅　を設定する
			&m->Height[cnt]);//MAP構造体の逆さに、画像の高さを設定する

		m->C_Width[cnt] = m->Width[cnt] / 2;//画像の横サイズの中心を取得
		m->C_Height[cnt] = m->C_Height[cnt] / 2;//画像の縦サイズの中心を取得
	}

	m->charaStopFlag = FALSE;//プレイヤーの移動制御フラグ
	return TRUE;
}

//########## CHARAを分割して読み込む設定をする関数 ##########
//引　数：CHARA構造体　：設定する画像構造体(分割)の変数
//引　数：int　：画像の分割数
//引　数：int　：画像の横の分割数
//引　数：int　：画像の縦の分割数
//引　数：int　：画像の横の分割サイズ
//引　数：int　：画像の縦の分割サイズ
//引　数：const char *：読み込む画像のファイルパス
//戻り値：BOOL：エラー時：FALSE
BOOL MY_CHARA_LOAD_BUNKATSU(CHARA *c, int bun_num, int bun_x_num, int bun_y_num, int bun_width, int bun_height, const char *path)
{
	int ret = 0;
	wsprintf(c->FilePath, path);//ファイルパスをコピー

	//画像をメモリに分割して読み込み、ハンドルを取得
	ret = LoadDivGraph(c->FilePath, bun_num, bun_x_num, bun_y_num, bun_width, bun_height, c->Handle);

	if (ret == -1) { return FALSE; }//画像読み込みエラー

	for (int cnt = 0; cnt < GAME_MAP_BUN_YOKO_CNT*GAME_MAP_BUN_TATE_CNT; cnt++)
	{
		//画像サイズを取得
		GetGraphSize(
			c->Handle[cnt],		//ハンドルから、画像の幅と高さを取得して・・・
			&c->Width[cnt],		//MAP構造体の幅　に、画像の幅　を設定する
			&c->Height[cnt]);	//MAP構造体の逆さに、画像の高さを設定する			

		c->C_Width[cnt] = c->Width[cnt] / 2;			//画像の横サイズの中心を取得
		c->C_Height[cnt] = c->Height[cnt] / 2;			//画像の縦サイズの中心を取得
	}

	return TRUE;
}

//########## プレイヤーを初期化する関数 ##########
//引　数：CHARA 構造体　  ：設定するPLAYER構造体
//引　数：PLAYER構造体　　：設定するCHARA構造体
//引　数：int* 　　 　　　：使用する画像の番号（配列の先頭アドレスを引数とする）
//引　数：int　	　　　　　：画像の初期位置X
//引　数：int　	　　　　　：画像の初期位置Y
//引　数：int　	　　　　　：移動スピード
//戻り値：BOOL：エラー時：FALSE
BOOL MY_INIT_PLAYER(PLAYER *p, CHARA c, int *num, int x, int y, int speed)
{
	//*(num + 0)は配列の先頭アドレス

	for (int mot = 0; mot < GAME_CHARA_MOTION_NUM; mot++)
	{
		p->Handle[mot] = c.Handle[*(num + mot)];	//画像のハンドルを入れる
	}

	p->X = x;
	p->Y = y;
	p->Width = c.Width[*(num + 0)];		//最初の画像の横幅を設定する
	p->Height = c.Height[*(num + 0)];	//最初の画像の高さを設定する
	p->C_Width = c.C_Width[*(num + 0)];	//最初の画像の横幅の中心を設定する
	p->C_Height = c.C_Height[*(num + 0)];	//最初の画像の高さの中心を設定する


	//マップひとつあたりと同じ大きさにする
	p->Width = GAME_MAP_YOKO_SIZE;
	p->Height = GAME_MAP_TATE_SIZE;
	p->C_Width = GAME_MAP_YOKO_SIZE / 2;
	p->C_Height = GAME_MAP_TATE_SIZE / 2;

	p->NowHandleNum = 6;	//右向きの最初の画像
	p->NowHandleCnt = 0;	//画像カウンタを初期化

	p->NowHandleCntMAX = 10;	//画像カウンタMAXを初期化

		//***** 以下、パラメータ設定 **************************************************

	p->Speed = speed;//移動速度を設定する
	p->MoveDist = x;//今の距離を、マップの最初から動いた距離として設定する

	p->CanMoveUp = TRUE;	//上に移動できる
	p->CanMoveDown = TRUE;	//下に移動できる

	p->CanMoveLeft = TRUE;	//左に移動できる
	p->CanMoveRight = TRUE;	//右に移動できる

	p->atariX = 8;			//当たり判定のX位置を、イイ感じに設定	※画像表示と当たり判定のX位置が同じとは、限らない
	p->atariY = 6;			//当たり判定のY位置を、イイ感じに設定	※画像表示と当たり判定のY位置が同じとは、限らない
	p->atariWidth = 16;		//当たり判定の幅　を、イイ感じに設定	※画像表示と当たり判定の幅が同じとは、限らない
	p->atariHeight = 26;	//当たり判定の高さを、イイ感じに設定	※画像表示と当たり判定の高さが同じとは、限らない

	MY_SET_PLAYER_ATARI(p);	//プレイヤーの当たり判定の領域を設定する

	return TRUE;

}



//########## プレイヤーを操作する関数 ##########
VOID MY_PLAY_PLAYER_OPERATION(VOID)
{
	BOOL IsKeyDown = FALSE;
	BOOL CanMoveUp = TRUE;					//上に行けるか
	BOOL CanMoveDown = TRUE;					//下に行けるか
	BOOL CanMoveLeft = TRUE;	//左に行けるか
	BOOL CanMoveRight = TRUE;	//右に行けるか

	//プレイヤーの位置がマップ配列のどこにいるか変換
	int PlayerToMapNumY;
	//プレイヤーの【移動した位置】がマップ配列のどこにいるか変換	※プレイヤーの位置は、スクロール時、変わらないため
	//キャラの位置を、１マップの半分の位置にする
	int PlayerToMapNumX;

	if (AllKeyState[KEY_INPUT_UP] != 0)	//上矢印キーが押されていた時
	{
		IsKeyDown = TRUE;	//キーを押された
		if (Myplayer.NowHandleCnt < Myplayer.NowHandleCntMAX)
		{
			Myplayer.NowHandleCnt++;
		}
		else
		{
			Myplayer.NowHandleCnt = 0;

			if (Myplayer.NowHandleNum >= 9 && Myplayer.NowHandleNum < 11)
			{
				Myplayer.NowHandleNum++;	//次の上向きの画像
			}
			else
			{
				Myplayer.NowHandleNum = 9;	//一番最初の上向きの画像
			}

		}

		//方向に、まだ動ける
		Myplayer.CanMoveUp = TRUE;

		MY_SET_PLAYER_ATARI(&Myplayer);	//プレイヤーの当たり判定の領域を設定
		Myplayer.atariRect.top -= 10;
		Myplayer.atariRect.bottom -= 10;

		if (MY_CHECK_RECT_ATARI_CHARA_MAP(Myplayer.atariRect, rectMap_UpNG) == TRUE)	//上に行けないモノと当たったとき
		{
			Myplayer.CanMoveUp = FALSE;	//上に行けない
		}

		if (Myplayer.CanMoveUp == TRUE)	//上に移動できるとき
		{

					Myplayer.Y -= Myplayer.Speed;	//プレイヤー移動

		}
	}

	if (AllKeyState[KEY_INPUT_DOWN] != 0)	//下矢印キーが押されていた時
	{
		IsKeyDown = TRUE;	//キーを押された
		if (Myplayer.NowHandleCnt < Myplayer.NowHandleCntMAX)
		{
			Myplayer.NowHandleCnt++;
		}
		else
		{
			Myplayer.NowHandleCnt = 0;

			if (Myplayer.NowHandleNum >= 0 && Myplayer.NowHandleNum < 2)
			{
				Myplayer.NowHandleNum++;	//次の下向きの画像
			}
			else
			{
				Myplayer.NowHandleNum = 0;	//一番最初の下向きの画像
			}

		}

		//方向に、まだ動ける
		Myplayer.CanMoveDown = TRUE;

		MY_SET_PLAYER_ATARI(&Myplayer);	//プレイヤーの当たり判定の領域を設定
		Myplayer.atariRect.top += 4;	
		Myplayer.atariRect.bottom += 4;	

		if (MY_CHECK_RECT_ATARI_CHARA_MAP(Myplayer.atariRect, rectMap_DownNG) == TRUE)	//下に行けないモノと当たったとき
		{
			Myplayer.CanMoveDown = FALSE;	//下に行けない
		}

		if (Myplayer.CanMoveDown == TRUE)	//下に移動できるとき
		{

					Myplayer.Y += Myplayer.Speed;	//プレイヤー移動

		}
	}

	if (AllKeyState[KEY_INPUT_LEFT] != 0)	//左矢印キーが押されていた時
	{
		IsKeyDown = TRUE;	//キーを押された

		if (Myplayer.NowHandleCnt < Myplayer.NowHandleCntMAX)
		{
			Myplayer.NowHandleCnt++;
		}
		else
		{
			Myplayer.NowHandleCnt = 0;

			if (Myplayer.NowHandleNum >= 3 && Myplayer.NowHandleNum < 5)
			{
				Myplayer.NowHandleNum++;	//次の左向きの画像
			}
			else
			{
				Myplayer.NowHandleNum = 3;	//一番最初の左向きの画像
			}
		}
		//左方向に、まだ動ける
		Myplayer.CanMoveLeft = TRUE;

		MY_SET_PLAYER_ATARI(&Myplayer);	//プレイヤーの当たり判定の領域を設定
		Myplayer.atariRect.left -= 8;	//少し、当たり判定の領域を左にずらす
		Myplayer.atariRect.right -= 8;	//少し、当たり判定の領域を左にずらす

		if (MY_CHECK_RECT_ATARI_CHARA_MAP(Myplayer.atariRect, rectMap_LeftNG) == TRUE)	//左に行けないモノと当たったとき
		{
			Myplayer.CanMoveLeft = FALSE;	//左に行けない
		}

		if (Myplayer.CanMoveLeft == TRUE)	//左に移動できるとき
		{
			if (MapImage.charaStopFlag == FALSE)	//プレイヤーが移動できるとき
			{
				if (Myplayer.X > 0)
				{
					Myplayer.X -= Myplayer.Speed;	//プレイヤーを左に移動
				}
			}

			if (Myplayer.MoveDist > 0)
			{
				Myplayer.MoveDist -= Myplayer.Speed;	//動いた距離を計算
			}
		}

	}

	if (AllKeyState[KEY_INPUT_RIGHT] != 0)	//右矢印キーが押されていた時
	{
		IsKeyDown = TRUE;	//キーを押された

		if (Myplayer.NowHandleCnt < Myplayer.NowHandleCntMAX)
		{
			Myplayer.NowHandleCnt++;
		}
		else
		{
			Myplayer.NowHandleCnt = 0;

			if (Myplayer.NowHandleNum >= 6 && Myplayer.NowHandleNum < 8)
			{
				Myplayer.NowHandleNum++;	//次の右向きの画像
			}
			else
			{
				Myplayer.NowHandleNum = 6;	//一番最初の右向きの画像
			}
		}
		//右方向に、まだ動ける
		Myplayer.CanMoveRight = TRUE;

		MY_SET_PLAYER_ATARI(&Myplayer);	//プレイヤーの当たり判定の領域を設定
		Myplayer.atariRect.left += 8;	//少し、プレイヤーの当たり判定の領域を右にずらす
		Myplayer.atariRect.right += 8;	//少し、プレイヤーの当たり判定の領域を右にずらす

		if (MY_CHECK_RECT_ATARI_CHARA_MAP(Myplayer.atariRect, rectMap_RightNG) == TRUE)	//右に行けないモノと当たったとき
		{
			Myplayer.CanMoveRight = FALSE;	//右に行けない

		}

		if (Myplayer.CanMoveRight == TRUE)	//右に移動できるとき
		{
			if (MapImage.charaStopFlag == FALSE)	//プレイヤーが移動できるとき（開始位置）
			{
				if (Myplayer.X + Myplayer.Width < GAME_WIDTH)
				{
					Myplayer.X += Myplayer.Speed;			//プレイヤーを右に移動
				}
			}

			if (Myplayer.MoveDist < GAME_MAP_YOKO_SIZE * GAME_MAP_YOKO)
			{
				Myplayer.MoveDist += Myplayer.Speed;	//動いた距離を計算
			}       

		}
	}

	//マップの左側にいるときは、プレイヤーを動かす
	if (Myplayer.MoveDist > 0 &&
		Myplayer.MoveDist <= GAME_MAP_YOKO_SIZE * 10)	//プレイヤーの動いた距離が一定以上あれば(開始地点)
	{
		MapImage.charaStopFlag = FALSE;					//マップを止めて、プレイヤーを動かす
	}

	//マップ真ん中らへんにいるときは、マップを動かす
	if (Myplayer.MoveDist > GAME_MAP_YOKO_SIZE * 10 &&
		Myplayer.MoveDist <= GAME_MAP_YOKO_SIZE * (GAME_MAP_YOKO - 10))	//プレイヤーの動いた距離が一定以上あれば(開始地点)
	{
		MapImage.charaStopFlag = TRUE;					//マップを動かす
	}

	//マップの右側にいるときは、プレイヤーを動かす
	if (Myplayer.MoveDist > GAME_MAP_YOKO_SIZE * (GAME_MAP_YOKO - 10) &&
		Myplayer.MoveDist <= GAME_MAP_YOKO_SIZE * GAME_MAP_YOKO)	//プレイヤーの動いた距離が一定以上あれば(終了地点)
	{
		MapImage.charaStopFlag = FALSE;					//マップを止めて、プレイヤーを動かす
	}

	//キーを押されていないとき
	if (IsKeyDown == FALSE)
	{
		if (Myplayer.NowHandleNum >= 3 && Myplayer.NowHandleNum <= 5)
		{
			//押されていないときは右向きの立ちポーズ
			Myplayer.NowHandleNum = 4;
		}
		else if (Myplayer.NowHandleNum >= 9 && Myplayer.NowHandleNum <= 11)
		{
			//押されていないときは左向きの立ちポーズ
			Myplayer.NowHandleNum = 10;
		}

		Myplayer.NowHandleCnt = Myplayer.NowHandleCntMAX - 1;	//すぐ画像を変えられるようにする
	}


	//マップの当たり判定もスクロールさせる
	for (int tate = 0; tate < GAME_MAP_TATE; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO; yoko++)
		{
			rectMap_DownNG[tate][yoko].left = rectMap_DownNG_First[tate][yoko].left - ScrollCntYoko;
			rectMap_DownNG[tate][yoko].right = rectMap_DownNG_First[tate][yoko].right - ScrollCntYoko;

			rectMap_DownOK[tate][yoko].left = rectMap_DownOK_First[tate][yoko].left - ScrollCntYoko;
			rectMap_DownOK[tate][yoko].right = rectMap_DownOK_First[tate][yoko].right - ScrollCntYoko;

			rectMap_LeftNG[tate][yoko].left = rectMap_LeftNG_First[tate][yoko].left - ScrollCntYoko;
			rectMap_LeftNG[tate][yoko].right = rectMap_LeftNG_First[tate][yoko].right - ScrollCntYoko;

			rectMap_RightNG[tate][yoko].left = rectMap_RightNG_First[tate][yoko].left - ScrollCntYoko;
			rectMap_RightNG[tate][yoko].right = rectMap_RightNG_First[tate][yoko].right - ScrollCntYoko;

			rectMap_UpNG[tate][yoko].left = rectMap_UpNG_First[tate][yoko].left - ScrollCntYoko;
			rectMap_UpNG[tate][yoko].right = rectMap_UpNG_First[tate][yoko].right - ScrollCntYoko;

		}
	}

	return;
}

//########## プレイヤーを表示する関数 ##########
VOID MY_PLAY_PLAYER_DRAW(VOID)
{
	//プレイヤーを拡大して描画
	DrawExtendGraph(
		Myplayer.X,
		Myplayer.Y,
		Myplayer.X + Myplayer.Width,
		Myplayer.Y + Myplayer.Height,
		Myplayer.Handle[Myplayer.NowHandleNum], TRUE);
	return;
}

//########## マップを表示する関数 ##########
VOID MY_PLAY_MAP_DRAW(VOID)
{
	//スクロールするマップを描画
	for (int tate = 0; tate < GAME_MAP_TATE; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO; yoko++)
		{
			if ((yoko + 1) * GAME_MAP_YOKO_SIZE - ScrollCntYoko >= 0 &&
				(yoko + 0) * GAME_MAP_YOKO_SIZE - ScrollCntYoko <= GAME_WIDTH)	//画面に写っているならばならば
			{
				DrawGraph(
					yoko * GAME_MAP_YOKO_SIZE - ScrollCntYoko,			//位置からスクロール量を引く
					tate * GAME_MAP_TATE_SIZE,
					MapImage.Handle[MapData[tate][yoko]], TRUE);		//マップをスクロールしながら描画

			/*	DrawBox(
					rectMap_DownNG[tate][yoko].left,
					rectMap_DownNG[tate][yoko].top,
					rectMap_DownNG[tate][yoko].right,
					rectMap_DownNG[tate][yoko].bottom,
					GetColor(255, 0, 0), FALSE);	//下に行けないマップ

				DrawBox(
					rectMap_DownOK[tate][yoko].left,
					rectMap_DownOK[tate][yoko].top,
					rectMap_DownOK[tate][yoko].right,
					rectMap_DownOK[tate][yoko].bottom,
					GetColor(0, 255, 255), FALSE);	//下に行けるマップ*/
			}
		}
	}
}
//########## 背景を表示する関数 ##########
VOID MY_PLAY_BACKIMAGE_DRAW(VOID)
{
		DrawGraph(
			BackImage[0].X,
			BackImage[0].Y,
			BackImage[0].Handle, FALSE);	//背景描画
	return;
}
VOID MY_PLAY_BACKIMAGE1_DRAW(VOID)
{
	DrawGraph(
		BackImage[1].X,
		BackImage[1].Y,
		BackImage[1].Handle, FALSE);	//背景描画
	return;
}
VOID MY_PLAY_BACKIMAGE2_DRAW(VOID)
{
	DrawGraph(
		BackImage[2].X,
		BackImage[2].Y,
		BackImage[2].Handle, FALSE);	//背景描画
	return;
}

//########## ゲーム画面のスクロールを行う関数 ##########
VOID MY_PLAY_SCROLL(VOID)
{
	ScrollCntYoko += ScrollDistPlusYoko;

	//DrawFormatString(0, 20, GetColor(255, 255, 255), "スクロールした量(横)：%06d", ScrollCntYoko);

	return;
}

//########## ゲームマップのCSVを読み込む関数 ##########
BOOL MY_MAP_READ_CSV_NUM                   (FILE *fp, const char *path)
{
	if ((fp = fopen(path, "r")) == NULL)//ファイルを読み込みモード(r)で開く
	{
		return FALSE;
	}//異常終了	

	//ここから正常に読み込めたときの処理****************************************

	int result = 0;			//ファイルの最後かチェック
	int LoopCnt = 0;		//ループカウンタ
	while (result != EOF)	//End Of File（ファイルの最後）ではないとき繰り返す
	{
		//ファイルから数値を一つ読み込み(%d,)、配列に格納する
		result = fscanf(fp, "%d,", &MapData[LoopCnt / GAME_MAP_YOKO][LoopCnt % GAME_MAP_YOKO]);

		MapData_Init[LoopCnt / GAME_MAP_YOKO][LoopCnt % GAME_MAP_YOKO] = MapData[LoopCnt / GAME_MAP_YOKO][LoopCnt % GAME_MAP_YOKO];	//値をコピー

		LoopCnt++;
	}

	fclose(fp);	//ファイルを閉じる


	int cnt;

	//マップを当たり判定の領域に変換
	for (int tate = 0; tate < GAME_MAP_TATE; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO; yoko++)
		{
			for (cnt = 0; cnt < GAME_MAP_NOTDOWN_KIND; cnt++)	//下に行けないマップ
			{
				if (MapData[tate][yoko] == MapNotDownKind[cnt])
				{
					rectMap_DownNG[tate][yoko].left = yoko * GAME_MAP_YOKO_SIZE + 1;
					rectMap_DownNG[tate][yoko].top = tate * GAME_MAP_TATE_SIZE + 1;
					rectMap_DownNG[tate][yoko].right = (yoko + 1) * GAME_MAP_YOKO_SIZE - 1;
					rectMap_DownNG[tate][yoko].bottom = (tate + 1) * GAME_MAP_TATE_SIZE - 1;

					rectMap_DownNG_First[tate][yoko] = rectMap_DownNG[tate][yoko];	//初期位置を設定

				}
			}

			for (cnt = 0; cnt < GAME_MAP_OKDOWN_KIND; cnt++)			//下に行けるマップ
			{
				if (MapData[tate][yoko] == MapOKDownKind[cnt])
				{
					rectMap_DownOK[tate][yoko].left = yoko * GAME_MAP_YOKO_SIZE + 1;
					rectMap_DownOK[tate][yoko].top = tate * GAME_MAP_TATE_SIZE + 1;
					rectMap_DownOK[tate][yoko].right = (yoko + 1) * GAME_MAP_YOKO_SIZE - 1;
					rectMap_DownOK[tate][yoko].bottom = (tate + 1) * GAME_MAP_TATE_SIZE - 1;

					rectMap_DownOK_First[tate][yoko] = rectMap_DownOK[tate][yoko];	//初期位置を設定

				}
			}

			for (cnt = 0; cnt < GAME_MAP_NOTLEFT_KIND; cnt++)			//左に行けないマップ
			{
				if (MapData[tate][yoko] == MapNotLeftKind[cnt])
				{
					rectMap_LeftNG[tate][yoko].left = yoko * GAME_MAP_YOKO_SIZE + 1;
					rectMap_LeftNG[tate][yoko].top = tate * GAME_MAP_TATE_SIZE + 1;
					rectMap_LeftNG[tate][yoko].right = (yoko + 1) * GAME_MAP_YOKO_SIZE - 1;
					rectMap_LeftNG[tate][yoko].bottom = (tate + 1) * GAME_MAP_TATE_SIZE - 1;

					rectMap_LeftNG_First[tate][yoko] = rectMap_LeftNG[tate][yoko];	//初期位置を設定

				}
			}

			for (cnt = 0; cnt < GAME_MAP_NOTRIGHT_KIND; cnt++)			//右に行けないマップ
			{
				if (MapData[tate][yoko] == MapNotRightKind[cnt])
				{
					rectMap_RightNG[tate][yoko].left = yoko * GAME_MAP_YOKO_SIZE + 1;
					rectMap_RightNG[tate][yoko].top = tate * GAME_MAP_TATE_SIZE + 1;
					rectMap_RightNG[tate][yoko].right = (yoko + 1) * GAME_MAP_YOKO_SIZE - 1;
					rectMap_RightNG[tate][yoko].bottom = (tate + 1) * GAME_MAP_TATE_SIZE - 1;

					rectMap_RightNG_First[tate][yoko] = rectMap_RightNG[tate][yoko];	//初期位置を設定

				}
			}

			for (cnt = 0; cnt < GAME_MAP_NOTUP_KIND; cnt++)			//上に行けないマップ
			{
				if (MapData[tate][yoko] == MapNotUpKind[cnt])
				{
					rectMap_UpNG[tate][yoko].left = yoko * GAME_MAP_YOKO_SIZE + 1;
					rectMap_UpNG[tate][yoko].top = tate * GAME_MAP_TATE_SIZE + 1;
					rectMap_UpNG[tate][yoko].right = (yoko + 1) * GAME_MAP_YOKO_SIZE - 1;
					rectMap_UpNG[tate][yoko].bottom = (tate + 1) * GAME_MAP_TATE_SIZE - 1;

					rectMap_UpNG_First[tate][yoko] = rectMap_UpNG[tate][yoko];	//初期位置を設定

				}
			}

		}
	}

	return TRUE;
}

//########## プレイヤーの当たり判定の領域を設定する関数 ##########
VOID MY_SET_PLAYER_ATARI(PLAYER *p)
{
	//当たり判定の領域の設定
	p->atariRect.left = p->X + p->atariX;						//現在のX位置 ＋ 当たり判定のX位置
	p->atariRect.top = p->Y + p->atariY;						//現在のY位置 ＋ 当たり判定のY位置
	p->atariRect.right = p->X + p->atariX + p->atariWidth - 1;		//現在のX位置 ＋ 当たり判定のX位置 ＋ 当たり判定の幅
	p->atariRect.bottom = p->Y + p->atariY + p->atariHeight - 1;	//現在のY位置 ＋ 当たり判定のY位置 ＋ 当たり判定の高さ

	return;
}

//########## 領域の当たり判定をする関数 ##########
BOOL MY_CHECK_RECT_ATARI(RECT a, RECT b)
{
	if (a.left < b.right &&
		a.top < b.bottom &&
		a.right > b.left &&
		a.bottom > b.top
		)
	{
		return TRUE;	//当たっている
	}

	return FALSE;		//当たっていない
}

//########## キャラクターとマップの当たり判定をする関数 ##########
//引　数　：RECT	：当たり判定をする領域(キャラクター)
//引　数　：RECT	：当たり判定をする領域(マップ)
//戻り値　：当たっている：TRUE / 当たっていない / FALSE
BOOL MY_CHECK_RECT_ATARI_CHARA_MAP(RECT chara, RECT map[GAME_MAP_TATE][GAME_MAP_YOKO])
{
	for (int tate = 0; tate < GAME_MAP_TATE; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO; yoko++)
		{
			//キャラクターの当たっている場所を取得
			if (MY_CHECK_RECT_ATARI(chara, map[tate][yoko]) == TRUE)
			{
				return TRUE;
			}
		}
	}

	return FALSE;		//当たっていない
}

//########## 音を読み込む設定をする関数 ##########
//引　数：音構造体　	:設定する音構造体の変数
//引　数：const char *	:読み込む画像のファイルパス
//戻り値：BOOL			:TRUE:正常 / FALSE:異常
BOOL MY_MUSIC_LOAD(MUSIC *m, const char *path)
{
	//音を読み込む
	m->Handle = LoadSoundMem(path);

	if (m->Handle == -1) { return FALSE; }

	return TRUE;
}