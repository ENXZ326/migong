
//########## ヘッダーファイル読み込み ##########
#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>

//########## マクロ定義 ##########
#define GAME_WIDTH	600	//画面の横の大きさ
#define GAME_HEIGHT	400	//画面の縦の大きさ
#define GAME_COLOR	32		//画面のカラービット

#define GAME_BACKGOUND		"BACK\\space4.jpg"				//背景画像
#define GAME_BACKGOUND1		""
#define GAME_CHARA_UFO		"CHARA\\UFO_mini.png"	//UFOの画像

#define FNT_TANU_PATH	TEXT("MY_FONT\\TanukiMagic.ttf")	//フォントの場所
#define FNT_TANU_NAME	TEXT("たぬき油性マジック")			//フォントの名前

#define GAME_WINDOW_NAME	"?????"

#define GAME_FPS_SPEED					   60

#define SET_WINDOW_ST_MODE_DEFAULT			0
#define SET_WINDOW_ST_MODE_TITLE_NONE		1
#define SET_WINDOW_ST_MODE_TITLE_FLAME_NONE	2
#define SET_WINDOW_ST_MODE_FLAME_NONE		3

//########## 列挙型 ##########
enum GAME_SCENE {
	GAME_SCENE_TITLE,//タイトル画面
	GAME_SCENE_PLAY,//プレイ画面
	GAME_SCENE_END//エンド画面
};

//########## 構造体 ##########
struct STRUCT_GAZOU {
	int Handle;				//画像のハンドル
	char FilePath[128];		//ファイルのパス
	int X;					//横の位置
	int Y;					//縦の位置
	int Width;				//横のサイズ
	int Height;				//縦のサイズ
	int C_Width;			//横の中心位置
	int C_Height;			//縦の中心位置
	int MoveSpeed;			//移動速度
	BOOL IsView;			//表示判定
};



//########## 名前の再定義 ##########
typedef STRUCT_GAZOU GAZOU;

//########## グローバル変数 ##########
GAZOU	BackGround;				//背景の画像
GAZOU	UFO1;					//UFOの画像
GAZOU	CRAB1;


char AllKeyState[256];			//すべてのキーの状態が入る

//FPS関連
int StartTimeFps;						//測定開始時刻
int CountFps;							//カウンタ
float CalcFps;							//計算結果
int SampleNumFps = GAME_FPS_SPEED;		//平均を取るサンプル数

int HFont_tanu_32;						//フォントのハンドル



int GameSceneNow = (int)GAME_SCENE_TITLE;//最初のゲーム画面をタイトルに設定

//########## プロトタイプ宣言 ##########

BOOL MY_GAZOU_LOAD(GAZOU *, int, int, const char *);			//画像を読み込む設定をする関数

VOID MY_DRAW_PLAY_INFO(VOID);

BOOL MY_FONT_CREATE(const char *, int *, int, int, int);		//フォントを読み込む関数
LRESULT CALLBACK MY_WNDPROC(HWND, UINT, WPARAM, LPARAM);		//自作ウィンドウプロシージャ

VOID MY_ALL_KEYDOWN_UPDATE(VOID);	//キーの入力状態を更新する関数

VOID MY_FPS_UPDATE(VOID);			//FPS値を計測、更新する関数
VOID MY_FPS_DRAW(VOID);				//FPS値を描画する関数
VOID MY_FPS_WAIT(VOID);				//FPS値を計測し、待つ関数
VOID MY_DRAW_PLAY_INFO(VOID);		//プレイ画面の情報を描画する関数
VOID MY_GAME_TITLE(VOID);			//タイトル画面の関数
VOID MY_GAME_END(VOID);				//エンド画面の関数

//########## プログラムで最初に実行される関数 ##########
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);										//ウィンドウモードに設定
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);			//指定の数値で画面を表示する
	SetWindowStyleMode(SET_WINDOW_ST_MODE_DEFAULT);			//タイトルバー
	//SetWindowStyleMode(SET_WINDOW_ST_MODE_TITLE_NONE);			//タイトルバーなし

	SetMainWindowText(TEXT(GAME_WINDOW_NAME));					//タイトルの文字


	if (DxLib_Init() == -1) { return -1; }						//ＤＸライブラリ初期化処理


	SetDrawScreen(DX_SCREEN_BACK);								//Draw系関数は裏画面に描画

	//画像を読み込む
	if (MY_GAZOU_LOAD(&BackGround, 0, 0, GAME_BACKGOUND) == FALSE) { return -1; }
	if (MY_GAZOU_LOAD(&UFO1, GAME_WIDTH / 2, GAME_HEIGHT / 2, GAME_CHARA_UFO) == FALSE) { return -1; }


	//無限ループ
	while (TRUE)
	{
		if (ProcessMessage() != 0) { break; }	//メッセージ処理の結果がエラーのとき、強制終了

		if (ClearDrawScreen() != 0) { break; }	//画面を消去できなかったとき、強制終了

		MY_ALL_KEYDOWN_UPDATE();				//押しているキー状態を取 得

		MY_FPS_UPDATE();	//FPSの処理[更新]

		//シーン選択
		switch (GameSceneNow)
		{
		case (int)GAME_SCENE_TITLE://タイトル画面の処理ここから

			MY_GAME_TITLE();

			break;//タイトル画面の処理ここまで

		case (int)GAME_SCENE_PLAY:

			if (AllKeyState[KEY_INPUT_UP] != 0)				//上に移動
			{
				if (UFO1.Y - UFO1.MoveSpeed > 0)	//自分の上の位置が、画面の一番上の位置よりも大きいとき
				{
					UFO1.Y -= UFO1.MoveSpeed;
				}
			}
			else if (AllKeyState[KEY_INPUT_DOWN] != 0)		//下に移動
			{
				if (UFO1.Y + UFO1.Height + UFO1.MoveSpeed < GAME_HEIGHT)	//自分の下の位置が、画面の一番下の位置よりも小さいとき
				{
					UFO1.Y += UFO1.MoveSpeed;
				}
			}
			if (AllKeyState[KEY_INPUT_LEFT] != 0)			//左に移動
			{
				if (UFO1.X - UFO1.MoveSpeed > 0)			//自分の左の位置が、画面の一番左の位置よりも大きいとき
				{
					UFO1.X -= UFO1.MoveSpeed;
				}
			}
			else if (AllKeyState[KEY_INPUT_RIGHT] != 0)		//右に移動
			{
				if (UFO1.X + UFO1.Width + UFO1.MoveSpeed < GAME_WIDTH)		//自分の右の位置が、画面の一番右の位置よりも小さいとき
				{
					UFO1.X += UFO1.MoveSpeed;
				}

			}

			//背景の描画
			DrawGraph(BackGround.X, BackGround.Y, BackGround.Handle, TRUE);

			if (UFO1.IsView == TRUE)
			{
				DrawGraph(UFO1.X, UFO1.Y, UFO1.Handle, TRUE);//UFOを描画
			}


			//四角形の中を塗りつぶさないで描画

			DrawBox(UFO1.X, UFO1.Y, UFO1.X + UFO1.Width, UFO1.Y + UFO1.Height, GetColor(0, 255, 255), FALSE);


			break;//プレイ画面の処理ここまで
		case (int)GAME_SCENE_END://エンド画面の処理ここから

			MY_GAME_END();

			break;//エンド画面の処理ここまで

		default:

			break;
		}

		MY_FPS_DRAW();		//FPSの処理[描画]

		ScreenFlip();		//モニタのリフレッシュレートの速さで裏画面を再描画

		MY_FPS_WAIT();		//FPSの処理[待つ]

	}

	DeleteFontToHandle(HFont_tanu_32);	//フォントのハンドルを削除

	DeleteGraph(BackGround.Handle);		//画像のハンドルを削除
	DeleteGraph(UFO1.Handle);			//画像のハンドルを削除
	//DeleteGraph(CRAB1.Handle);			//画像のハンドルを削除

	DxLib_End();		//ＤＸライブラリ使用の終了処理

	return 0;

}

//########## タイトル画面の関数 ##########
VOID MY_GAME_TITLE(VOID)
{
	if (AllKeyState[KEY_INPUT_RETURN] != 0)//エンターキーを押したとき
	{
		GameSceneNow = (int)GAME_SCENE_PLAY;//プレイ画面にする
	}

	//背景の描画
	DrawGraph(BackGround.X, BackGround.Y, BackGround.Handle, TRUE);

	//表示する文字列
	char title1[64] = "あ~そ`ぼ~う";
	//デフォルトのフォントを変更する
	ChangeFont("MS ゴシック", DX_CHARSET_DEFAULT);
	//デフォルトのフォントサイズを変える
	SetFontSize(64);
	//フォントをきれいにみせる
	ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE);
	//デフォルトのフォントの横幅を取得
	int TitleStringWidth1 = GetDrawFormatStringWidth(title1);
	//デフォルトのフォントの高さを取得
	int TitleStringHeight1 = GetFontSize();
	//デフォルトのフォントで描画
	DrawFormatString(GAME_WIDTH / 2 - TitleStringWidth1 / 2, GAME_HEIGHT / 2, GetColor(255, 255, 255), title1);

	//表示する文字列
	char title2[64] = " GAME START";
	//デフォルトのフォントを変更する
	ChangeFont("MS 明朝", DX_CHARSET_DEFAULT);
	//デフォルトのフォントサイズを変える
	SetFontSize(48);
	//フォントをきれいにみせる
	ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE);
	//デフォルトのフォントの横幅を取得
	int TitleStringWidth2 = GetDrawFormatStringWidth(title2);
	//デフォルトのフォントの高さを取得
	int TitleStringHeight2 = GetFontSize();
	//デフォルトのフォントで描画
	DrawFormatString(GAME_WIDTH / 2 - TitleStringWidth2 / 2, GAME_HEIGHT / 2 + TitleStringHeight1, GetColor(255, 255, 255), title2);

	return;

}

//########## エンド画面の関数 ##########
VOID MY_GAME_END(VOID)
{
	char EndWin[64] = "GAME OVER";

	//デフォルトのフォントを変更する
	ChangeFont("MS ゴシック", DX_CHARSET_DEFAULT);
	//デフォルトのフォントサイズを変える
	SetFontSize(100);
	//フォントをきれいにみせる
	ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE);
	//タイトル文字１の横幅を取得
	int EmdStringWidth1 = GetDrawFormatStringWidth(EndWin);
	//タイトル文字１の高さを取得
	int EndStringHeight1 = GetFontSize();

	//背景の描画
	DrawGraph(BackGround.X, BackGround.Y, BackGround.Handle, TRUE);
	DrawFormatString(GAME_WIDTH / 2 - EmdStringWidth1 / 2, GAME_HEIGHT / 2, GetColor(255, 255, 255), "GAME OVER");

	if (AllKeyState[KEY_INPUT_SPACE] != 0)
	{
		GameSceneNow = (int)GAME_SCENE_TITLE;
	}



	return;
}
//########## プレイ画面の情報を描画する関数 ##########
VOID MY_DRAW_PLAY_INFO(VOID)
{
	if (UFO1.IsView == TRUE)
	{
		DrawGraph(UFO1.X, UFO1.Y, UFO1.Handle, TRUE);//UFOを描画
	}

	//四角形の中を塗りつぶさないで描画

	DrawBox(UFO1.X, UFO1.Y, UFO1.X + UFO1.Width, UFO1.Y + UFO1.Height, GetColor(0, 255, 255), FALSE);
	//DrawBox(CRAB1.X, CRAB1.Y, CRAB1.X + CRAB1.Width, CRAB1.Y + CRAB1.Height, GetColor(0, 255, 255), FALSE);



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

//########## FPS値を計測、更新する関数 ##########
VOID MY_FPS_UPDATE(VOID)
{
	if (CountFps == 0) //1フレーム目なら時刻を記憶
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

	//フォントハンドルを使用して文字列を描画
	DrawFormatStringToHandle(0, 0, GetColor(255, 255, 255), HFont_tanu_32, "FPS:%.1f", CalcFps);

	return;
}

//########## FPS値を計測し、待つ関数 ##########
VOID MY_FPS_WAIT(VOID)
{
	int resultTime = GetNowCount() - StartTimeFps;					//かかった時間
	int waitTime = CountFps * 1000 / GAME_FPS_SPEED - resultTime;	//待つべき時間

	if (waitTime > 0)	//早すぎる分、待機
	{
		Sleep(waitTime);
	}
	return;
}

//########## フォントを読み込む関数 ##########
//引　数：const char *：読み込むフォントの名前
//引　数：int *：フォントのハンドル
//引　数：int　：フォントの大きさ
//引　数：int　：フォントの太さ
//引　数：int　：フォントのタイプ
//戻り値：なし→変更→戻り値：BOOL：エラー時：FALSE
BOOL MY_FONT_CREATE(const char *name, int *f, int pt, int bold, int type)
{
	*f = CreateFontToHandle(name, pt, bold, type);	//フォントハンドル作成
	if (*f == -1) { return FALSE; }					//作成失敗

	return TRUE;
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

	g->MoveSpeed = 4;									//移動速度
	g->IsView = TRUE;

	return TRUE;
}