#include "DxLib.h"
#include "iostream"
#define SCREEN_WIDTH     (1920)                          // 画面の横幅
#define SCREEN_HEIGHT    (1080)                          // 画面の縦幅
#define CHIP_SIZE        (128)                           // 一つのチップのサイズ
#define MAP_WIDTH        (SCREEN_WIDTH / CHIP_SIZE)      // マップの横幅
#define MAP_HEIGHT       (SCREEN_HEIGHT / CHIP_SIZE)     // マップの縦幅

#define MAP_N 8
#define MAP_M 8

#define G                (0.3F)                         // キャラに掛かる重力加速度
#define JUMP_POWER       (10.0F)                         // キャラのジャンプ力
#define SPEED            (5.0F)                         // キャラの移動スピード
#define MAX_SPEED_X      (5.0F)                         // キャラのX最大スピード
#define MAX_SPEED_Y      (12.0F)                         // キャラのY最大スピード
#define MAX_BLOCK_SPEED_Y      (10.0F)                         // キャラのY最大スピード
#define DECCEL           (1.0F)                         // キャラの原則スピード

#define MAX_JUMPTIME     (14.0F)

#define MAX_ROTATION_TIME  4*10
#define MAX_INVERSION_TIME 4*10
#define MAX_DAMAGE_TIME 4*10

#define MAX_BLACKOUT_TIME 30
#define MAX_WHITEOUT_TIME 30


#define CHAR_SIZE        (64)                           // プレイヤーのサイズ


#define BLOCK_MAX 9 //1ステージの最大ブロック数

// マップデータ
int MapData[MAP_N][MAP_M] ={};
//プレイヤーの位置を保存する配列
int playerData[MAP_N][MAP_M] = {};

int Stage1[MAP_N][MAP_M] =
{
0,0,0,-1,-1,-1,-1,1,
0,0,0,-1,-1,-1,-1,-1,
0,0,0,-1,-1,0,0,0,
0,0,0,-1,-1,0,0,0,
0,0,0,-1,-1,0,0,0,
0,0,0,-1,-1,0,0,0,
-1,-1,-1,-1,-1,0,0,0,
-1,-1,-1,-1,-1,0,0,0,

};
int Stage2[MAP_N][MAP_M] =
{
0,1,0,0,0,0,0,0,
0,-1,0,0,0,0,0,0,
0,-1,-1,-1,-1,-1,0,0,
0,0,0,0,0,-1,0,0,
0,0,0,0,0,-1,0,0,
0,0,0,0,0,-1,0,0,
0,-1,-1,-1,-1,-1,-1,0,
0,-1,0,0,0,0,0,0,


};
int Stage3[MAP_N][MAP_M] =
{
-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,0,-1,-1,-1,
-1,-1,-1,0,-1,-1,-1,-1,
-1,-1,0,-1,1,-1,-1,-1,
-1,-1,0,-1,-1,-1,-1,-1,
-1,-1,0,-1,-1,-1,-1,-1,

};
int Stage4[MAP_N][MAP_M] =
{
-1,-1,-1,0,0,-1,-1,-1,
-1,-1,-1,0,0,-1,-1,1,
-1,-1,-1,-1,-1,-1,-1,-1,
0,0,-1,0,0,-1,0,0,
0,0,-1,0,0,-1,0,0,
-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,0,0,-1,-1,-1,
-1,-1,-1,0,0,-1,-1,-1,

};
int Stage5[MAP_N][MAP_M] =
{
 -1,-1,0,-1,-1,-1,-1,-1,
-1,-1,0,-1,0,-1,-1,1,
-1,-1,0,-1,0,0,0,0,
-1,0,0,-1,-1,-1,-1,-1,
3,-1,-1,3,-1,0,0,-1,
0,0,0,0,-1,0,-1,-1,
-1,-1,-1,0,-1,0,-1,-1,
-1,-1,-1,-1,3,0,-1,3,


};
int Stage6[MAP_N][MAP_M] =
{
0,0,-1,-1,-1,0,0,0,
0,0,0,-1,0,0,0,0,
0,0,0,-1,0,0,0,0,
-1,0,-1,-1,3,0,0,-1,
-1,-1,-1,-1,3,-1,-1,1,
-1,0,-1,-1,3,0,0,-1,
0,0,0,-1,0,0,0,0,
0,0,-1,-1,-1,0,0,0,


};
int Stage7[MAP_N][MAP_M] =
{
 0,-1,-1,-1,-1,-1,-1, 0,
-1, 0, 0,-1, 1,-1, 0,-1,
-1,-1,-1, 0,-1,-1, 0,-1,
-1,-1,-1,-1,-1, 0,-1,-1,
-1,-1, 0,-1,-1,-1,-1,-1,
-1, 0,-1,-1, 0,-1,-1,-1,
-1, 0,-1,-1,-1, 0, 0,-1,
 0,-1,-1,-1,-1,-1,-1, 0,

};
int Stage8[MAP_N][MAP_M] =
{
-1,-1,-1,-1,-1,-1,-1, 0,
-1, 0,-1, 2, 0,-1,-1, 2,
-1, 2,-1,-1, 2,-1,-1, 0,
 2, 0,-1,-1, 1,-1,-1,-1,
-1,-1,-1, 2, 0, 2, 0,-1,
-1, 0,-1,-1, 2,-1, 2,-1,
-1,-1, 0,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1, 0, 2,-1,

};
int Stage9[MAP_N][MAP_M] =
{
-1,-1,-1,-1,-1,-1,-1, 0,
-1, 0,-1,-1,-1,-1, 0, 1,
-1,-1, 0,-1,-1, 0,-1,-1,
-1,-1,-1, 0, 0,-1,-1,-1,
-1,-1,-1, 0, 0,-1,-1,-1,
-1,-1, 0,-1,-1, 0,-1,-1,
-1, 0,-1,-1,-1,-1, 0,-1,
-1,-1,-1,-1,-1,-1,-1,-1,


};
int Stage10[MAP_N][MAP_M] =
{
 2, 2, 2, 2, 2, 2, 2, 2,
-1,-1,-1,-1,-1,-1,-1, 1,
 0,-1,-1,-1,-1,-1,-1,-1,
-1,-1, 0, 0, 0, 0, 0, 0,
-1,-1,-1,-1,-1,-1, 0, 0,
-1,-1,-1,-1,-1,-1,-1, 0,
-1,-1,-1,-1,-1,-1,-1,-1,
 0, 0, 0,-1,-1,-1, 0, 0,

};
int Stage11[MAP_N][MAP_M] =
{
 0, 2, 2, 2, 2, 2, 2, 0,
 0,-1, 0,-1,-1,-1, 1, 0,
 0,-1,-1,-1,-1,-1, 0, 0,
 0,-1,-1, 0,-1,-1,-1, 0,
 0,-1,-1, 0,-1,-1,-1, 2,
 0, 0, 0,-1,-1,-1,-1, 2,
 2,-1,-1,-1, 2, 0, 2, 2,
 0, 0, 0, 0, 2, 2, 2, 0,


};
int Stage12[MAP_N][MAP_M] =
{
 0, 0,-1,-1, 0,-1,-1, 1,
 0,-1,-1, 0, 0,-1, 0, 0,
 0,-1, 0,-1,-1,-1, 0,-1,
 0,-1, 0,-1, 0, 0,-1,-1,
-1,-1,-1,-1,-1,-1,-1, 0,
-1, 0,-1, 0,-1, 0, 0,-1,
 0,-1,-1, 0,-1, 0, 0,-1,
 0,-1, 0,-1,-1,-1,-1,-1,

};
int Stage13[MAP_N][MAP_M] =
{
 0, 2, 2, 2, 2, 2, 2, 0,
 2, 0, 2,-1, 1,-1,-1, 2,
 2,-1,-1,-1, 0,-1,-1, 2,
 2,-1,-1, 0,-1,-1, 0, 2,
 0,-1,-1,-1,-1,-1,-1, 0,
 2, 0,-1,-1,-1,-1,-1, 2,
 2,-1,-1,-1,-1,-1, 0, 2,
 2,-1,-1,-1,-1, 0,-1, 2,

};
int Stage14[MAP_N][MAP_M] =
{
-1,-1,-1,-1,-1,-1, 1, 0,
-1,-1,-1,-1,-1,-1, 0, 0,
-1,-1,-1, 0, 0, 0, 0, 0,
 0,-1,-1,-1,-1,-1,-1, 0,
 0,-1,-1,-1,-1,-1,-1, 0,
 0, 0, 0, 0, 0,-1,-1,-1,
 0, 0,-1,-1,-1,-1,-1,-1,
 0,-1,-1,-1,-1,-1,-1,-1,

};
int Stage15[MAP_N][MAP_M] =
{
 0, 2, 2, 2, 2, 2, 2, 0,
 2,-1, 0,-1,-1,-1, 0, 2,
 2, 0, 2,-1,-1,-1, 0, 2,
 2,-1,-1,-1,-1,-1,-1, 2,
 2,-1,-1, 0,-1,-1,-1, 2,
 2,-1,-1, 0,-1,-1, 0, 2,
 2,-1, 0, 1,-1, 0,-1, 2,
 0, 2, 2, 2, 2, 2, 2, 0,

};
int Stage16[MAP_N][MAP_M] =
{
 2, 2, 0, 1, 2, 2, 2, 2,
 2,-1, 0,-1,-1, 2, 0, 2,
 2,-1,-1, 0,-1,-1,-1, 2,
 2, 2,-1,-1,-1, 0,-1, 2,
 2,-1,-1, 0,-1,-1,-1, 0,
 2, 0,-1,-1,-1, 2,-1, 2,
 2,-1, 0,-1,-1,-1,-1, 2,
 2, 2, 2, 0, 2, 0, 0, 2,

};
int Stage17[MAP_N][MAP_M] =
{
 2, 2, 0, 0, 1,-1,-1,-1,
 0, 0, 2,-1,-1, 0, 2, 0,
 2, 2, 0, 0,-1, 2, 0, 2,
 0, 0, 2, 2,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1, 0, 0,
-1, 2, 0,-1, 0, 0, 2, 2,
-1, 0, 2,-1, 2, 2, 0, 0,
-1,-1,-1,-1, 0, 0, 2, 2,

};
int Stage18[MAP_N][MAP_M] =
{
 2,-1,-1, 2, 1, 2,-1, 2,
-1, 2,-1, 2,-1, 2,-1,-1,
 2,-1, 2,-1,-1,-1, 2,-1,
-1, 0,-1,-1, 0,-1,-1,-1,
-1,-1,-1, 0, 2,-1, 2,-1,
-1,-1,-1,-1, 2,-1, 2,-1,
 0,-1,-1,-1, 2,-1,-1,-1,
-1,-1, 0,-1, 2, 2,-1,-1,
};
int Stage19[MAP_N][MAP_M] =
{
 2,-1,-1, 0, 2,-1,-1, 2,
-1,-1, 0, 2, 2,-1,-1,-1,
-1,-1,-1,-1,-1,-1, 0, 1,
 2, 2,-1, 2, 2,-1, 2, 0,
 0, 2,-1, 2, 2,-1, 2, 2,
-1, 0,-1,-1,-1,-1,-1,-1,
-1,-1,-1, 2, 2, 0,-1,-1,
 2,-1,-1, 2, 0,-1,-1, 2,

};
int Stage20[MAP_N][MAP_M] =
{
 2,-1,-1,-1,-1,-1, 0, 2,
-1,-1, 0,-1,-1,-1,-1,-1,
-1, 0, 2, 2, 2,-1,-1,-1,
-1,-1, 0, 0,-1,-1,-1,-1,
-1,-1, 0, 0, 1,-1,-1,-1,
-1,-1, 0, 0,-1, 2,-1,-1,
 0,-1, 2,-1,-1, 2, 2,-1,
 2, 0, 2,-1,-1,-1,-1, 2,
};


//黒ブロックの位置を保存する配列
int blackData[MAP_N][MAP_M] = {};
//ステージごとのブロック数
const int BlackCount[20] = {
    0,1,1,7,4,
    3,7,0,6,9,
    0,4,0,8,0,
    0,1,1,0,3
};
//黒ブロックの初期マス
struct VECTOR2 {
    int x, y;
};
const VECTOR2 BlackPos[20][BLOCK_MAX] = {
    {{}},
    {{1,2}},
    {{7,7}},
    {{3,2},{4,2},{7,2},{2,5},{3,5},{2,6},{2,7}},
    {{0,4},{3,4},{4,7},{7,7}},

    {{4,3},{4,4},{4,5}},
    {{2,2},{4,2},{2,3},{4,3},{4,4},{3,6},{3,7}},
    {{}},
    {{1,0},{6,4},{4,5},{6,5},{4,6},{4,7}},
    {{0,1},{0,4},{1,4},{0,5},{1,5},{2,5},{0,6},{1,6},{2,6}},

    {{}},
    {{2,1},{5,2},{2,6},{4,7}},
    {{}},
    {{3,0},{3,1},{3,3},{4,3},{3,4},{4,4},{4,6},{4,7}},
    {{}},

    {{}},
    {{3,1}},
    {{7,7}},
    {{}},
    {{1,6},{3,7},{6,7}},
};



//一時的に保持しておくマップデータ
int TempMapData[MAP_N][MAP_M] =
{
    0
};
int TempPlayerData[MAP_N][MAP_M] =
{
    0
};
int TempBlackData[MAP_N][MAP_M] = {};

//リトライ用マップデータ（初期位置）
int RetryData[MAP_N][MAP_M] =
{
    0
};

//TODO: 変数置き場

//回転に必要な変数
int n;  
int m;
int cnt;

//当たり判定用
struct Box {
    float left;
    float right;
    float top;
    float bottom;
};

//プレイヤー用
//float PlX = 256, PlY = 1024;            // プレイヤーの座標(中心座標)   //TODO:ここ初期化の時もう一度したほうがいいんじゃないか
//float PlDownSp;            // プレイヤーの落下速度
//char PlJumpFlag;           // プレイヤーがジャンプ中か、のフラグ

struct Player {
    float x, y; //位置
    float speedX,speedY;    //速度        //VECTOR2にしてぇぇ
    bool onGround;  //着地フラグ

    int animeTime;//画像に使用する秒数
    bool Xflip;//向いている方向(右:false、左:true)


    bool rotationFlag;   //回転フラグ   trueにすれば時間が増え、回転が終わったら時間0になる
    bool inversionFlag;   //反転フラグ　trueにすれば時間が増え、回転が終わったら時間0になる
    bool damageFlag;    //ダメージフラグ


    //時間を画像に使っている
    int fallTimer;  //落下時間
    int jumpTimer;  //ジャンプ時間
    int damageTimer;//ダメージ時間
    int rotationTimer;//回転時間
    int inversionTimer;//反転時間
    int clearTimer;//クリア時間

};

Player player = {};

//ブロック用
//float blockX, blockY; //ブロック座標（中心）
//float BlackDownSp;
//bool blockGround;       //ブロックが地面についているか
int moveblock[1];

//ブロック構造体
struct Block {
    float x, y; //位置
    float speed; //速度
    bool onGround;  //着地フラグ
    bool spawn; //存在するか   判定取るときに使うかも(存在しないはずのものと当たり判定を取らないように)
    int No;//識別(黒ブロック同士の判定に使う)
};

Block black[BLOCK_MAX] = {};


int Input, EdgeInput;      // 入力状態
int FrameStartTime;        // ６０ＦＰＳ固定用、時間保存用変数



//ステージ変更
bool NextStage = false;         //TODO:　ここだけで初期化してると後で初期化し忘れそう
bool ResetStage = false;
bool ClearStage = false;    //クリアしたか、使いまわしでブラックアウトに使ってたりする。
bool ReturnStage = false;
int StageCnt = 0;

int WhiteTimer = 0;//経過時間
int BlackTimer = 0;//経過時間

bool WhiteOut = false;//フラグ
bool BlackOut = false;//フラグ

bool ColorMax = false;//ブラックアウトホワイトアウトに使う(ブラックアウトホワイトアウト処理内で完結)

int BlackBack;//画像
int WhiteBack;//画像

bool SpecialAction = false;
//特殊行動(回転・反転・リセット)の時に他の特殊行動が出来ないように
//trueにすると他の特殊行動や移動が出来なくなる


//ステージずらしの位置補正
const float stageoffsetX= SCREEN_WIDTH / 4 - 64;
const float stageoffsetY= (SCREEN_HEIGHT -CHIP_SIZE*8)/2;//余白分/2(真ん中に)
//const float stageoffsetX= 0;


//プレイヤーアニメーション
int PlayerAnime[56];//待機

//アニメーションの順番
int walkNo[4] = { 7,8,9,8 };
//踏ん張りの画像場所
int animeJumpImage[4] = { 29,30,31,32 };
//反転の画像
int animeInversion[5] = {22,23,24,25,26};
//回転の画像
int animeRotation[5] = {15,16,17,18,19};
//ダメージの画像
int animeDamage[3] = {43,44,45};
//クリアモーションの画像
int animeClear[7] = { 50,51,52,53,54,55,56 };
//アニメの種類別の数
int animeType[8] = { 1,3,5,5,4,1,3,7 };

//float playerOffsetX = CHAR_SIZE;
float playerOffsetY = 20;



//UI
int UI_Inversion;
int UI_Rotation;
int UI_Reset;
int UI_Select;


//画面推移
int NowSc = 1;
int Title;

int gamemode = 1;


//HACK:サウンド関係

int titleBGM;
int selectBGM;
int gameBGM;

int rotationSe = LoadSoundMem("サウンド/rotation.mp3");



//プレイヤーの回転用
int plxr, plyr;

//ステージ画像
int StageImg[10];


//背景画像
int back;
int frame;

//セレクト背景描画
int selectbg;
int selection[20];
int selectImg[5];
int offset=64;

int scrollCnt = 0;

//クリア背景画像
int clearText[5];
int clearIcon[3];

//HACK: 触った
//とげの当たり判定用
float needleOffset = 25;


// マップチップの値を取得する関数
int GetChipParam(float X, float Y);

// キャラクタをマップとの当たり判定を考慮しながら移動する関数
int CharMove(Player& player, float Size);
//int CharMove(float* X, float* Y, float* DownSP,
//    float MoveX, float MoveY, float Size, char* JumpFlag);

//TODO:   PlayerClearRender
void playerClearRender()
{
    int playerHandle = {};//描画する画像
    int X1 = 400;
    int Y1 = 790;
    int devisionTime = 4;
    playerHandle = PlayerAnime[animeClear[player.clearTimer / 10 % 6]];
    DrawGraph(X1, Y1, playerHandle, TRUE);
    player.clearTimer++;
}


//普通ブロックかを返す関数
bool isHit(float x, float y)
{
    return(GetChipParam(x, y) == 0);    //普通ブロックを0にしているから画面外でも０で取れてる
}

//壁か判定する関数
bool isWall(float x, float y, float height)//想定は基準点が真ん中下基準
{
    for (; height > 0; height -= CHIP_SIZE)
    {
        const float yPos = y - height;//マップチップ1つよりでかい場合。下から上に順々に見ている(上で減らしているので)
        //画面外なら
        if (yPos < 0)      continue;
        if (yPos > SCREEN_HEIGHT) continue;

        if (isHit(x, yPos))
            return true;
    }
    return isHit(x, y);
}

//天井か判定する関数
bool isCeiling(float x, float y, float width)
{
    for (; width > 0; width -= CHIP_SIZE)
    {
        const float left = x - width;
        const float right = x + width;

        // エリアチェック
        if (left < 0)       continue;
        if (right >= SCREEN_WIDTH) continue;

        if (isHit(left, y))  return true;
        if (isHit(right, y)) return true;
    }
    return isHit(x, y);
}

//床か判定する関数
bool isFloor(float x, float y, float width)
{
    for (; width > 0; width -= CHIP_SIZE)       // widthをCHIP_SIZE分減らしていく
    {
        const float left = x - width;
        const float right = x + width;

        // エリアチェック
        if (left < 0)       continue;
        if (right >= SCREEN_WIDTH) continue;

        if (isHit(left, y))  return true;   // 左端から
        if (isHit(right, y)) return true;   // 右端から
    }
    return isHit(x, y);                     // 最後に真ん中で判定
}


//黒ブロック
//その場所が配列的に見て同じマスか
bool isBlack(float x,float y);

//天井か判定する関数
bool isCeilingBlack(float x, float y, float width)
{
    for (; width > 0; width -= CHIP_SIZE)
    {
        const float left = x - width;
        const float right = x + width;

        // エリアチェック
        if (left < 0)       continue;
        if (right >= SCREEN_WIDTH) continue;

        if (isBlack(left, y))  return true;
        if (isBlack(right, y)) return true;
    }
    return isBlack(x, y);
}

//床か判定する関数
bool isFloorBlack(float x, float y, float width)
{
    for (; width > 0; width -= CHIP_SIZE)       // widthをCHIP_SIZE分減らしていく
    {
        const float left = x - width;
        const float right = x + width;

        // エリアチェック
        if (left < 0)       continue;
        if (right >= SCREEN_WIDTH) continue;

        if (isBlack(left, y))  return true;   // 左端から
        if (isBlack(right, y)) return true;   // 右端から
    }
    return isBlack(x, y);                     // 最後に真ん中で判定
}


//HACK: 触った

//
//とげブロックかを返す関数
bool isHitNeedle(float x, float y)
{
    return(GetChipParam(x, y) == 2);    //普通ブロックを0にしているから画面外でも０で取れてる
}

//壁がトゲか判定する関数
bool isWallNeedle(float x, float y, float height)//想定は基準点が真ん中下基準
{
    for (; height > 0; height -= CHIP_SIZE)
    {
        const float yPos = y - height;//マップチップ1つよりでかい場合。下から上に順々に見ている(上で減らしているので)
        //画面外なら
        if (yPos < 0)      continue;
        if (yPos > SCREEN_HEIGHT) continue;

        if (isHitNeedle(x, yPos))
            return true;
    }
    return isHitNeedle(x, y);
}

//左右がとげか判定する関数
bool isNeedle(float x, float y, float height)//想定は基準点が真ん中下基準
{
    for (; height > 0; height -= CHIP_SIZE)
    {
        const float yPos = y - height;//マップチップ1つよりでかい場合。下から上に順々に見ている(上で減らしているので)
        //画面外なら
        if (yPos < 0)      continue;
        if (yPos > SCREEN_HEIGHT) continue;

        if (isHitNeedle(x, yPos))
            return true;
    }
    return isHitNeedle(x, y);
}
//天井がとげか判定する関数
bool isCeilingNeedle(float x, float y, float width)
{
    for (; width > 0; width -= CHIP_SIZE)
    {
        const float left = x - width;
        const float right = x + width;

        // エリアチェック
        if (left < 0)       continue;
        if (right >= SCREEN_WIDTH) continue;

        if (isHitNeedle(left, y))  return true;
        if (isHitNeedle(right, y)) return true;
    }
    return isHitNeedle(x, y);
}

//床がとげか判定する関数
bool isFloorNeedle(float x, float y, float width)
{
    for (; width > 0; width -= CHIP_SIZE)       // widthをCHIP_SIZE分減らしていく
    {
        const float left = x - width;
        const float right = x + width;

        // エリアチェック
        if (left < 0)       continue;
        if (right >= SCREEN_WIDTH) continue;

        if (isHitNeedle(left, y))  return true;   // 左端から
        if (isHitNeedle(right, y)) return true;   // 右端から
    }
    return isHitNeedle(x, y);                     // 最後に真ん中で判定
}
//

//当たり判定用
bool hitCheck(Box box1,Box box2)
{
    if (box1.right < box2.left) return false;
    if (box1.left > box2.right) return false;
    if (box1.bottom < box2.top) return false;
    if (box1.top > box2.bottom) return false;

    return true;
}


//そのマスに被っている黒ブロックを返す
Block& whoBlack(float x, float y);

//ブロック同士の当たり判定
bool blackHitBlack(Block& Black);

//ブロックとマップとの当たり判定を考慮しながら移動する関数
int BlackMove(Block& black,float Size);

// アクションサンプルプログラムメイン関数
int ActMain(void);

//ブロック用
int BlackMapHitCheck(float X, float Y, float* MoveX, float* MoveY);

//全ブロックが着地しているか
bool isBlackStop() {
    int blackGround = 0;//着地済みブロック
    if (black[0].spawn == true)//一つ目のブロックがあるなら
    {
        for (int i = 0; i < BlackCount[StageCnt]; i++) {
            if (black[i].onGround)
                blackGround++;
        }
    }
    if (blackGround == BlackCount[StageCnt])
        return true;
    return false;
}

void TitleSc();

void SelectSc();

//リセット関数
void resetStage() {
    ResetStage = true;
    BlackOut = true;
    SpecialAction = true;
}

//ブラックホワイト関数

//変数の初期化
void BlackWhiteInit() {

    WhiteTimer = 0;
    BlackTimer = 0;

    WhiteOut = false;
    BlackOut = false;

    ColorMax = false;
}

//画像のロード
void BlackWhiteLoad() {
    //ブラックアウトホワイトアウト
    BlackBack = LoadGraph("画像/black.png");
    WhiteBack = LoadGraph("画像/white.png");
}

//描画
void BlackOutRender()
{
    if (BlackOut) {
        int alpha = BlackTimer * (255 / MAX_BLACKOUT_TIME) * 3;
        if (alpha >= 255)alpha = 255;

        SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
        DrawGraph(0, 0, BlackBack, true);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

        //DrawFormatString(0, 9 * 12, GetColor(0, 0, 0), "alpha %d です", alpha);
        if (ColorMax && BlackTimer == 0)//半分過ぎて表示し終わったら
        {
            ColorMax = false;
            BlackOut = false;
        }
    }
}
void WhiteOutRender() {
    if (WhiteOut) {
        int alpha = WhiteTimer * (255 / MAX_WHITEOUT_TIME) * 3;
        if (alpha >= 255)alpha = 255;

        SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
        DrawGraph(0, 0, WhiteBack, true);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

        //DrawFormatString(0, 9 * 12, GetColor(0, 0, 0), "alpha %d です", alpha);
        if (ColorMax && WhiteTimer == 0)//半分過ぎて表示し終わったら
        {
            ColorMax = false;
            WhiteOut = false;
        }
    }
}

//時間関係(描画の後ろに)
void BlackOutTimer()//時間関係
{
    //ブラックアウトホワイトアウト(するならフラグを立てる)
    if (BlackOut) {
        //加算
        if (!ColorMax)BlackTimer++;
        else BlackTimer--;//描画する時間半分過ぎたら

        //フラグ
        if (BlackTimer == MAX_BLACKOUT_TIME / 2) {//半分なら
            ColorMax = true;
        }
        //制限
        //if (BlackTimer > MAX_BLACKOUT_TIME) {//最大)
        //    BlackTimer = MAX_BLACKOUT_TIME;
        //}
        if (BlackTimer < 0) {//最大
            BlackTimer = 0;
        }
    }
}
void WhiteOutTimer() {
    if (WhiteOut) {
        //加算
        if (!ColorMax)WhiteTimer++;
        else WhiteTimer--;//描画する時間半分過ぎたら

        //フラグ
        if (WhiteTimer == MAX_WHITEOUT_TIME / 2) {//半分なら
            ColorMax = true;
        }
        //制限
        //if (WhiteTimer > MAX_WHITEOUT_TIME) {//最大)
        //    WhiteTimer = MAX_WHITEOUT_TIME;
        //}
        if (WhiteTimer < 0) {//最大
            WhiteTimer = 0;
        }
    }
}




//初期化関数
void playerInit()
{
    // プレイヤーの落下速度を初期化
    player.speedY = 0.0F;
    player.speedX = 0.0f;
    // ジャンプ中フラグを倒す
    player.onGround = false;
    //プレイヤーのアニメの初期化
    player.animeTime = 0;
    //プレイヤーの左右
    player.Xflip = false;
    //プレイヤー特殊行動フラグ
    player.rotationFlag = false;
    player.inversionFlag = false;
    player.damageFlag = false;

    //プレイヤーの時間の初期化
    player.fallTimer = 0;
    player.jumpTimer = 0;
    player.damageTimer = false;
    player.rotationTimer = 0;
    player.inversionTimer = 0;
    player.clearTimer = 0;
}

void blackInit()
{
    for (int i = 0; i < BLOCK_MAX; i++)
    {
        black[i].x = 0;
        black[i].y = 0;
        black[i].speed = 0;
        black[i].spawn = false;
        black[i].onGround = false;
        black[i].No = 0;
    }
}

void stageSet()
{
    if (StageCnt == 0) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                MapData[i][j] = Stage1[i][j];
                RetryData[i][j] = Stage1[i][j];

            }
        }
        player.x = 216; //108
        player.y = 1024 - 64; //512
        //blockX = 129* 1;
        //blockY = 70 * 3;

    }
    if (StageCnt == 1) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                MapData[i][j] = Stage2[i][j];
                RetryData[i][j] = Stage2[i][j];

            }
        }
        player.x = 216; //108
        player.y = 1024 - 64; //512
        //blockX = 129* 1;
        //blockY = 70 * 3;

    }
    if (StageCnt == 2) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                MapData[i][j] = Stage3[i][j];
                RetryData[i][j] = Stage3[i][j];

            }
        }
        player.x = 108 * 1;
        player.y = 1024;


    }
    if (StageCnt == 3) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                MapData[i][j] = Stage4[i][j];
                RetryData[i][j] = Stage4[i][j];

            }
        }
        player.x = 108 * 1;
        player.y = 118 * 3;
    }
    if (StageCnt == 4) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                MapData[i][j] = Stage5[i][j];
                RetryData[i][j] = Stage5[i][j];

            }
        }
        player.x = 108 * 2;
        player.y = 1024;

    }
    if (StageCnt == 5) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                MapData[i][j] = Stage6[i][j];
                RetryData[i][j] = Stage6[i][j];

            }
        }
        player.x = 108 * 5;
        player.y = 1024;
    }
    if (StageCnt == 6) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                MapData[i][j] = Stage7[i][j];
                RetryData[i][j] = Stage7[i][j];

            }
        }
        player.x = 108 * 7;
        player.y = 1024;
    }
    if (StageCnt == 7) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                MapData[i][j] = Stage8[i][j];
                RetryData[i][j] = Stage8[i][j];

            }
        }
        player.x = 108 * 3;
        player.y = 118 * 6;
    }
    if (StageCnt == 8) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                MapData[i][j] = Stage9[i][j];
                RetryData[i][j] = Stage9[i][j];

            }
        }
        player.x = 108 * 7;
        player.y = 118 * 1;

    }
    if (StageCnt == 9) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                MapData[i][j] = Stage10[i][j];
                RetryData[i][j] = Stage10[i][j];

            }
        }
        player.x = 108 * 6;
        player.y = 1024;
    }
    if (StageCnt == 10) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                MapData[i][j] = Stage11[i][j];
                RetryData[i][j] = Stage11[i][j];

            }
        }
        player.x = 108 * 2;
        player.y = 118 * 7;
    }
    if (StageCnt == 11) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                MapData[i][j] = Stage12[i][j];
                RetryData[i][j] = Stage12[i][j];

            }
        }
        player.x = 108 * 4;
        player.y = 118 * 1;
    }
    if (StageCnt == 12) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                MapData[i][j] = Stage13[i][j];
                RetryData[i][j] = Stage13[i][j];

            }
        }
        player.x = 108 * 4;
        player.y = 1024;
    }
    if (StageCnt == 13) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                MapData[i][j] = Stage14[i][j];
                RetryData[i][j] = Stage14[i][j];

            }
        }
        player.x = 108 * 8;
        player.y = 1024;
    }
    if (StageCnt == 14) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                MapData[i][j] = Stage15[i][j];
                RetryData[i][j] = Stage15[i][j];

            }
        }
        player.x = 108 * 3;
        player.y = 118 * 6;
    }
    if (StageCnt == 15) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                MapData[i][j] = Stage16[i][j];
                RetryData[i][j] = Stage16[i][j];

            }
        }
        player.x = 108 * 7;
        player.y = 118 * 7;
    }
    if (StageCnt == 16) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                MapData[i][j] = Stage17[i][j];
                RetryData[i][j] = Stage17[i][j];

            }
        }
        player.x = 108 * 4;
        player.y = 1024;
    }
    if (StageCnt == 17) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                MapData[i][j] = Stage18[i][j];
                RetryData[i][j] = Stage18[i][j];

            }
        }
        player.x = 108 * 1;
        player.y = 1024;
    }
    if (StageCnt == 18) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                MapData[i][j] = Stage19[i][j];
                RetryData[i][j] = Stage19[i][j];

            }
        }
        player.x = 108 * 7;
        player.y = 1024;
    }
    if (StageCnt == 19) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                MapData[i][j] = Stage20[i][j];
                RetryData[i][j] = Stage20[i][j];

            }
        }
        player.x = 108 * 1;
        player.y = CHIP_SIZE * 6;
    }

}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    ChangeWindowMode(TRUE);
    SetWindowSize(1920, 1080);
    SetGraphMode(1920, 1080, 32, 60);
    // ＤＸライブラリの初期化
    if (DxLib_Init() == -1) return -1;

    //画像のロード
    //プレイヤー画像
    LoadDivGraph("画像/player.png", 56, 7, 8, 128, 128, PlayerAnime);


    //ブラックホワイトの初期化
    BlackWhiteInit();
    BlackWhiteLoad();

    ActMain();

    // ＤＸライブラリの後始末
    DxLib_End();
    // 終了
    return 0;
}

void TitleSc(void)
{
    //画面推移
    DrawGraph(0, 0, Title, true);

    if (CheckHitKeyAll(DX_CHECKINPUT_ALL)) {
        if (!BlackOut) {
            PlaySoundFile("サウンド/decision.wav", DX_PLAYTYPE_BACK); //効果音
        }
        BlackOut = true;
        ClearStage = true;

    }
    if (ClearStage&&ColorMax) {
        StopSoundMem(titleBGM);
        gamemode++;//セレクト初期化へ
        ClearStage = false;
    }
}

void SelectSc(void)
{
       DrawGraph(0, 0, back, true);

       int oldNum=scrollCnt / 5;//古い数値
        if (CheckHitKey(KEY_INPUT_A) && scrollCnt > 0) {
            scrollCnt--;

            //StageCnt--; //ステージカウント減らす
            //NextStage = true;
        }
        if (CheckHitKey(KEY_INPUT_D) && scrollCnt < 19*5) {
            scrollCnt++;
            

            //StageCnt++; //ステージカウント増やす
            //NextStage = true;
        }

        if (scrollCnt <= 0)scrollCnt = 0;
        if (scrollCnt >= 19*5)scrollCnt = 19*5;
        int Num = scrollCnt / 5;
        if (oldNum != Num) {
            PlaySoundFile("サウンド/cursor.wav", DX_PLAYTYPE_BACK); //効果音
        }
        //DrawRotaGraph(300, SCREEN_HEIGHT / 2, 1, 0, selecticon[1], true); //1の描画？？？？

        int selectX = 400;
        for (int i = 0; i < 5; i++) {
            
            if (i + Num > 19)break;
                DrawRotaGraph(selectX + 300 * i, SCREEN_HEIGHT / 2, 1, 0, selection[i + Num], true); //同時に6枚のみ描画
                //DrawFormatString(0, 20 * i, GetColor(0, 0, 0), "うーんこれは変数i = %d", i);
                if (i == 0)
                {
                    DrawRotaGraph(selectX + 300 * i, SCREEN_HEIGHT / 2, 1.3, 0, selection[i + Num], true); //同時に6枚のみ描画

                }
        }

        //矢印
        if(Num !=0)
        DrawRotaGraph(70,              SCREEN_HEIGHT / 2, 1, 0, selectImg[2], true);//右
        if(Num !=19)
        DrawRotaGraph(SCREEN_WIDTH - 70,SCREEN_HEIGHT / 2, 1, 0, selectImg[3], true);//左

        //タイトル
        DrawRotaGraph(500, 150, 1.3f, 0, selectImg[0], true);

        //説明
        DrawRotaGraph(SCREEN_WIDTH/2, 1010, 1, 0, selectImg[1], true);

        //UI
        DrawRotaGraph(100,980, 1,0, selectImg[4], true);
        

        //タイトル画面遷移&ブラックアウト
        if (CheckHitKey(KEY_INPUT_Z)) { //0key
            BlackOut = true;
            ReturnStage = true;//使いまわし
            //StopSoundFile();
        }
        if (ReturnStage && ColorMax) {
            gamemode=1;
            ReturnStage = false;
        }

        //ゲーム画面遷移&ブラックアウト
    if (CheckHitKey(KEY_INPUT_SPACE)) { //0key
        if (!ClearStage) {
            PlaySoundFile("サウンド/decision.wav", DX_PLAYTYPE_BACK); //効果音
        }
        BlackOut = true;
        ClearStage = true;//使いまわし
        //StopSoundFile();
    }
    
    if (ClearStage && ColorMax) {
        StageCnt = Num;
        gamemode++;
        StopSoundMem(selectBGM);
        ClearStage = false;
    }
   
}

void ClearSc()//クリア
{
    DrawGraph(0, 0, back, true);

    int oldNum= scrollCnt / 5;
    if (CheckHitKey(KEY_INPUT_W) && scrollCnt > 0) {
        scrollCnt--;

        //StageCnt--; //ステージカウント減らす
        //NextStage = true;
    }
    if (CheckHitKey(KEY_INPUT_S) && scrollCnt < 2 * 5) {
        scrollCnt++;
        //StageCnt++; //ステージカウント増やす
        //NextStage = true;
    }

    //if (scrollCnt <= 0)scrollCnt = 0;
    //if (scrollCnt >= 3 * 5)scrollCnt = 3 * 5;
    int Num = scrollCnt / 5;
    if (Num < 0)Num = 0;
    if (Num > 2)Num = 2;

    if(oldNum!=Num)
        PlaySoundFile("サウンド/cursor.wav", DX_PLAYTYPE_BACK); //効果音
    //テキスト
    VECTOR2 pos[3] = {
        {100 * 10,   100 * 5.5},
        {100 * 10+55,100 * 7+40},
        {100 * 10,   100 * 8.5}
    };
    float scale[3] = { 1.3f,1.3f,1.3f };
    scale[Num] *= 1.3f;

    DrawRotaGraph(pos[0].x, pos[0].y, scale[0], 0, clearText[2], true); ////次へ
    DrawRotaGraph(pos[1].x, pos[1].y, scale[1], 0, clearText[3], true); ////もう一回
    DrawRotaGraph(pos[2].x, pos[2].y, scale[2], 0, clearText[4], true); ////戻る

    //アイコン
    VECTOR2 pos2[3] = {
        {100 * 6.5,   100 * 5.5},
        {100 * 6.5,100 * 7 },
        {100 * 6.5,   100 * 8.5}
    };
    DrawRotaGraph(pos2[0].x, pos2[0].y, 1.3f, 0, clearIcon[0], true); //同時に6枚のみ描画
    DrawRotaGraph(pos2[1].x, pos2[1].y, 1.3f, 0, clearIcon[1], true); //同時に6枚のみ描画
    DrawRotaGraph(pos2[2].x, pos2[2].y, 1.3f, 0, clearIcon[2], true); //同時に6枚のみ描画
        

    //タイトル
    DrawRotaGraph(930, 300, 1.3f, 0, clearText[0], true);

    //説明
    DrawRotaGraph(1500, 1010, 1.0f, 0, clearText[1], true);

    //プレイヤー
    playerClearRender();

    //DrawFormatString(0, 15 * 2, GetColor(0, 0, 0), "ステージnumber%d", StageCnt);
    if (CheckHitKey(KEY_INPUT_SPACE)) { //0key
        BlackOut = true;
        ClearStage = true;//使いまわし
        //StopSoundMem(selectBGM);
        //StopSoundFile();
    }

    if (ClearStage && ColorMax) {
        if (ColorMax) {
            switch (Num)
            {
            case 0:
                StageCnt++;
                gamemode = 5;
                break;
            case 1:
                gamemode = 5;
                break;
            case 2:
                gamemode = 3;
                break;
            }
        }
        ClearStage = false;
    }

}

void stopBGM()
{
    StopSoundMem(titleBGM);
    StopSoundMem(gameBGM);
    StopSoundMem(selectBGM);
}

int ActMain(void)
{
    // 描画先を裏画面にセット
    SetDrawScreen(DX_SCREEN_BACK);

    // 垂直同期信号を待たない
    SetWaitVSyncFlag(FALSE);


    //タイトル画像
    //LoadDivGraph("画像/title.png", 1, 1, 1, 1920, 1080, Title);

    //ステージ画像
    LoadDivGraph("画像/mapchip.png", 4, 4, 1, 128, 128, StageImg);
    //ブロック
    LoadDivGraph("画像/moveblock.png", 1, 1, 1, 128, 128, moveblock);

    //背景画像
    back = LoadGraph("画像/back.png");
    frame = LoadGraph("画像/frame.png");



    //UI
    UI_Inversion = LoadGraph("画像/UI_L.png");
    UI_Rotation = LoadGraph("画像/UI_K.png");
    UI_Reset = LoadGraph("画像/UI_X.png");
    UI_Select = LoadGraph("画像/UI_Z.png");

    //プレイヤーの初期化
    playerInit();
    player.x = 256;
    player.y = 1000;


    NextStage = false;
    ResetStage = false;

    SpecialAction = false;

    ////ステージ初期化
    //for (int i = 0; i < 8; i++) {
    //    for (int j = 0; j < 8; j++) {
    //        MapData[i][j] = Stage1[i][j];
    //        RetryData[i][j] = Stage1[i][j];
    //
    //    }
    //}


     //TODO: ブロック初期化
     //BlackDownSp = 0.0F;
     //黒ブロックの初期化
    blackInit();


    // 入力状態の初期化
    Input = 0;
    EdgeInput = 0;




    // ６０ＦＰＳ固定用、時間保存用変数を現在のカウント値にセット
    FrameStartTime = GetNowCount();

    // メインループ開始、ＥＳＣキーで外に出る
    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {
        // 画面のクリア
        ClearDrawScreen();

        // １/６０秒立つまで待つ
        while (GetNowCount() - FrameStartTime < 1000 / 60) {}
        // 現在のカウント値を保存
        FrameStartTime = GetNowCount();
        {
            switch (gamemode)
            {
            case 1://タイトル初期化

                //ロード
                titleBGM = LoadSoundMem("サウンド/title.mp3");
                Title = LoadGraph("画像/title.png");

                stopBGM();

                PlaySoundMem(titleBGM, DX_PLAYTYPE_LOOP, TRUE);//音出す
                //音deinitで削除しないといけないとかあるかな

                //StopSoundMem(titleBGM);

                gamemode++;
                break;
            case 2://タイトル
                TitleSc();
                
                break;

            case 3://セレクト初期化
                //ロード
                selectBGM = LoadSoundMem("サウンド/select.mp3");

                stopBGM();

                PlaySoundMem(selectBGM, DX_PLAYTYPE_LOOP, TRUE);//音出す

                //ロード
                selectbg = LoadGraph("画像/select.png");
                selection[0] = LoadGraph("画像/ステージ1.png");
                selection[1] = LoadGraph("画像/ステージ2.png");
                selection[2] = LoadGraph("画像/ステージ3.png");
                selection[3] = LoadGraph("画像/ステージ4.png");
                selection[4] = LoadGraph("画像/ステージ5.png");
                selection[5] = LoadGraph("画像/ステージ6.png");
                selection[6] = LoadGraph("画像/ステージ7.png");
                selection[7] = LoadGraph("画像/ステージ8.png");
                selection[8] = LoadGraph("画像/ステージ9.png");
                selection[9] = LoadGraph("画像/ステージ10.png");
                selection[10] = LoadGraph("画像/ステージ11.png");
                selection[11] = LoadGraph("画像/ステージ12.png");
                selection[12] = LoadGraph("画像/ステージ13.png");
                selection[13] = LoadGraph("画像/ステージ14.png");
                selection[14] = LoadGraph("画像/ステージ15.png");
                selection[15] = LoadGraph("画像/ステージ16.png");
                selection[16] = LoadGraph("画像/ステージ17.png");
                selection[17] = LoadGraph("画像/ステージ18.png");
                selection[18] = LoadGraph("画像/ステージ19.png");
                selection[19] = LoadGraph("画像/ステージ20.png");

                selectImg[0]= LoadGraph("画像/selectText.png");  //タイトル
                selectImg[1]= LoadGraph("画像/selectText_0.png");//説明
                selectImg[2]= LoadGraph("画像/arrowLeft.png"); //矢印左
                selectImg[3]= LoadGraph("画像/arrowRight.png");//矢印右
                selectImg[4]= LoadGraph("画像/UI_Z.png");//UI


                ReturnStage = false;

                //初期化
                scrollCnt = 0;

                gamemode++;

            case 4:
                SelectSc();
                break;

            case 5://メイン初期化

                gameBGM = LoadSoundMem("サウンド/game.mp3");

                stopBGM();

                PlaySoundMem(gameBGM, DX_PLAYTYPE_LOOP, TRUE);//音出す

                playerInit();

                if (player.damageFlag) {
                    player.damageFlag = false;
                    player.damageTimer = 0;
                }

                blackInit();
                //黒ブロック設置
                for (int i = 0; i < BlackCount[StageCnt]; i++) {//ブロックのある数だけ
                    black[i].x = 128 * BlackPos[StageCnt][i].x + CHIP_SIZE / 2;  //真ん中に
                    black[i].y = 128 * BlackPos[StageCnt][i].y + CHIP_SIZE / 2;
                    black[i].spawn = true;
                    black[i].No = i;
                }

                stageSet();

                //ステージずれ補正
                if (NextStage)NextStage = false;
                if (ResetStage)ResetStage = false;

                //特殊行動終わり
                if (SpecialAction)SpecialAction = false;


                gamemode++;

            case 6://メイン
            {
                //背景描画
                DrawGraph(0, 0, back, true);
                DrawGraph(389, 0, frame, true);//フレーム描画
                    

                // プレイヤーの移動処理
                {
                    if (isBlackStop()) {
                        if (!SpecialAction) {
                            if (CheckHitKey(KEY_INPUT_A)) {//左
                                player.speedX -= SPEED;
                                player.Xflip = true;
                            }
                            else if (CheckHitKey(KEY_INPUT_D)) {//右
                                player.speedX += SPEED;
                                player.Xflip = false;
                            }
                            else {//押していない
                                if (player.speedX > 0) {
                                    player.speedX -= DECCEL;
                                    if (player.speedX < 0)player.speedX = 0.0f;
                                }
                                if (player.speedX < 0) {
                                    player.speedX += DECCEL;
                                    if (player.speedX > 0)player.speedX = 0.0f;
                                }
                            }

                            // 左右の移動を見る
                            /*
                            switch (Input & (PAD_INPUT_LEFT | PAD_INPUT_RIGHT))
                            {
                            case PAD_INPUT_LEFT:player.speedX -= SPEED;  player.Xflip = true; break;
                            case PAD_INPUT_RIGHT:player.speedX += SPEED; player.Xflip = false; break;
                            default://押してない
                                if (player.speedX > 0) {
                                    player.speedX -= DECCEL;
                                    if (player.speedX < 0)player.speedX = 0.0f;
                                }
                                if (player.speedX < 0) {
                                    player.speedX += DECCEL;
                                    if (player.speedX > 0)player.speedX = 0.0f;
                                }
                                break;
                            }
                            */

                            //if ((Input & PAD_INPUT_LEFT) != 0)  player.speedX -= SPEED;
                            //if ((Input & PAD_INPUT_RIGHT) != 0) player.speedX += SPEED;
                            // 地に足が着いている場合のみジャンプボタン(ボタン１ or Ｚキー)を見る
                        }
                    }

                    if (!player.damageFlag) {
                        // 落下処理
                        player.speedY += G;
                    }

                    //左右押しっぱで回転すると押さなくても移動するので
                    if (!isBlackStop())player.speedX = 0.0f;

                    //ジャンプ
                    if (isBlackStop()) {
                        if (!SpecialAction) {
                            //if (player.onGround == true && (EdgeInput & PAD_INPUT_C) != 0)
                            if (player.onGround == true && CheckHitKey(KEY_INPUT_SPACE))
                            {
                                player.speedY = -JUMP_POWER;
                                player.onGround = false;

                            }
                        }
                    }

                    //// 落下速度を移動量に加える
                    //MoveY = PlDownSp;

                    // 移動量に基づいてキャラクタの座標を移動
                    CharMove(player, CHAR_SIZE);

                    //画面外補正(多めに返す)(引っかかるので)
                    float offset = 0.025f;
                    if (player.x - CHAR_SIZE / 2 < 0)player.x = CHAR_SIZE / 2 + offset;//左
                    if (player.x + CHAR_SIZE / 2 > CHIP_SIZE * 8.0f)player.x = CHIP_SIZE * 8.0f - CHAR_SIZE / 2 - offset;//右
                    if (player.y - CHAR_SIZE < 0)player.y = CHAR_SIZE + offset;//上
                    if (player.y > CHIP_SIZE * 8.0f)player.y = CHIP_SIZE * 8.0f - offset;//下

                    //CharMove(&PlX, &PlY, &PlDownSp, MoveX, MoveY, CHAR_SIZE, &PlJumpFlag);


                }

                // ブロックの移動処理
                {
                    float BMoveX, BMoveY;

                    // 移動量の初期化
                    BMoveX = 0.0F;
                    BMoveY = 0.0F;

                    for (int i = 0; i < BlackCount[StageCnt]; i++) {
                        if (!black[i].onGround) {  //足ついていないなら
                            // 落下処理
                            black[i].speed += G * 0.9;

                            // 落下速度を移動量に加える //これ必要?
                            //BMoveY = BlackDownSp
                        }
                        //移動量に基づいてキャラクタの座標を移動
                        BlackMove(black[i], CHIP_SIZE);
                    }
                }

                //HACK:質問

                // マップの描画
                {
                    int i, j;
                    for (i = 0; i < 8; i++)
                    {
                        for (j = 0; j < 8; j++)
                        {
                            // 足ばチップの描画
                            if (MapData[i][j] == 0)
                            {
                                //DrawBox(j * CHIP_SIZE, i * CHIP_SIZE,
                                //    j * CHIP_SIZE + CHIP_SIZE, i * CHIP_SIZE + CHIP_SIZE,
                                //    GetColor(255, 255, 155), TRUE);
                                DrawGraph(j * CHIP_SIZE + stageoffsetX, i * CHIP_SIZE + stageoffsetY, StageImg[0], TRUE);
                                //DrawBox(j * CHIP_SIZE+stageoffsetX, i* CHIP_SIZE + stageoffsetY, j * CHIP_SIZE+CHIP_SIZE + stageoffsetX, i * CHIP_SIZE + CHIP_SIZE + stageoffsetY, GetColor(1, 1, 1), 0);

                            }
                            //ゴールチップの描画
                            if (MapData[i][j] == 1)
                            {
                                //DrawBox(j * CHIP_SIZE, i * CHIP_SIZE,
                                //    j * CHIP_SIZE + CHIP_SIZE, i * CHIP_SIZE + CHIP_SIZE,
                                //    GetColor(100, 255, 255), TRUE);
                                DrawGraph(j * CHIP_SIZE + stageoffsetX, i * CHIP_SIZE + stageoffsetY, StageImg[1], TRUE);


                            }
                            //とげの描画
                            if (MapData[i][j] == 2)
                            {
                                //HACK: 触った

    /*                       //      DrawBox(j * CHIP_SIZE, i * CHIP_SIZE,
                                     j * CHIP_SIZE + CHIP_SIZE, i * CHIP_SIZE + CHIP_SIZE,
                                     GetColor(100, 155, 255), TRUE);*/
                                DrawGraph(j * CHIP_SIZE + stageoffsetX, i * CHIP_SIZE + stageoffsetY, StageImg[2], TRUE);

                                //DrawCircle(j*CHIP_SIZE+CHIP_SIZE/2 + stageoffsetX, i* CHIP_SIZE+CHIP_SIZE/2 + stageoffsetY, 5, GetColor(1, 0, 1), 0);
                                //DrawBox(j* CHIP_SIZE + stageoffsetX, i* CHIP_SIZE + stageoffsetY+needleOffset, j *CHIP_SIZE+ CHIP_SIZE + stageoffsetX, i *CHIP_SIZE+ CHIP_SIZE+ stageoffsetY-needleOffset,
                                //GetColor(1, 0.6f, 1), 0);
                            }
                            //ブロックの描画
                            //if (MapData[i][j] == 3)
                            //{
    /*                        //      DrawBox(j * CHIP_SIZE, i * CHIP_SIZE,
                              //        j * CHIP_SIZE + CHIP_SIZE, i * CHIP_SIZE + CHIP_SIZE,
                              //        GetColor(100, 155, 255), TRUE);*/
                              //    DrawGraph(j* CHIP_SIZE + j, i* CHIP_SIZE, StageImg[3], TRUE);
                              //}
                        }
                    }
                }


                //ステージリセットフラグ
                //if (!SpecialAction&&player.onGround && Input & PAD_INPUT_X) {
                if (!SpecialAction && player.onGround && CheckHitKey(KEY_INPUT_X)) {
                    resetStage();

                }

                //戻る
                if (!SpecialAction && player.onGround && CheckHitKey(KEY_INPUT_Z)) {
                    ReturnStage = true;
                    BlackOut = true;
                }
                if (ReturnStage && ColorMax) {
                    gamemode = 3;
                }

                //ステージの処理
                if (NowSc != 2) {
                    if (isBlackStop()) {

                        //マップの反転
                        //if (!SpecialAction&&player.onGround&&EdgeInput & PAD_INPUT_A) {//反転フラグ
                        if (!SpecialAction && player.onGround && CheckHitKey(KEY_INPUT_L)) {//反転フラグ
                            //プレイヤー
                            player.speedX = 0.0f;
                            //フラグ立て
                            player.inversionFlag = true;

                            SpecialAction = true;

                            PlaySoundFile("サウンド/inversion.mp3", DX_PLAYTYPE_BACK); //効果音
                        }

                        //アニメーション終わりなら
                        if (player.inversionFlag && player.inversionTimer >= MAX_INVERSION_TIME) {

                            WhiteOut = true;
                            if (ColorMax) {//真っ白なら

                                //配列の引数を求める
                                plxr = (player.x) / 128;
                                plyr = (player.y) / 128;
                                TempPlayerData[plyr][plxr] = 1;
                                for (int i = 0; i < 8; i++) {
                                    for (int j = 0; j < 8; j++) {
                                        MapData[i][j] = TempMapData[i][7 - j];
                                        playerData[i][j] = TempPlayerData[i][7 - j];
                                    }
                                }
                                //プレイヤー位置検索
                                for (int i = 0; i < 8; i++) {
                                    for (int j = 0; j < 8; j++) {
                                        if (playerData[i][j] != 0)
                                        {
                                            player.x = j * 128 + 64;
                                            player.y = i * 128 + 64;
                                            playerData[i][j] = 0;

                                        }
                                        TempPlayerData[i][j] = 0;
                                    }
                                }

                                //黒ブロック

                                //配列の引数を決める
                                {
                                    for (int i = 0; i < BlackCount[StageCnt]; i++) {
                                        int bxr = (black[i].x) / 128;
                                        int byr = (black[i].y) / 128;
                                        TempBlackData[byr][bxr] = 1;
                                    }
                                }
                                //配列に回転させた位置保存
                                for (int i = 0; i < 8; i++) {
                                    for (int j = 0; j < 8; j++) {
                                        blackData[i][j] = TempBlackData[i][7 - j];
                                    }
                                }
                                //ブロック位置検索
                                {
                                    int n = 0;
                                    for (int i = 0; i < 8; i++) {
                                        for (int j = 0; j < 8; j++) {
                                            if (blackData[i][j] != 0) {
                                                //座標に戻す
                                                black[n].x = j * 128 + 64;
                                                black[n].y = i * 128 + 64;
                                                blackData[i][j] = 0;
                                                n++;
                                            }
                                            TempBlackData[i][j] = 0;
                                        }
                                    }
                                }

                                //特殊行動終わり
                                if (SpecialAction)SpecialAction = false;

                                //初期化
                                player.inversionFlag = false;
                                player.inversionTimer = 0;
                            }

                        }

                        //90度回転
                        //if (!SpecialAction&&player.onGround&&EdgeInput & PAD_INPUT_B) {//押して
                        if (!SpecialAction && player.onGround && CheckHitKey(KEY_INPUT_K)) {//押して
                            //プレイヤー
                            player.speedX = 0.0f;
                            //フラグ立て
                            player.rotationFlag = true;//描画用

                            SpecialAction = true;

                            PlaySoundFile("サウンド/rotation.mp3", DX_PLAYTYPE_BACK); //効果音
                        }

                        //アニメーション終わりなら
                        if (player.rotationFlag && player.rotationTimer >= MAX_ROTATION_TIME) {//最大時間


                            WhiteOut = true;
                            if (ColorMax) {//真っ白なら
                            //配列の引数を求める 
                                plxr = (player.x) / 128;
                                plyr = (player.y) / 128;
                                TempPlayerData[plyr][plxr] = 1;
                                //配列に回転させた位置保存
                                for (int i = 0; i < 8; i++) {
                                    for (int j = 0; j < 8; j++) {
                                        MapData[i][j] = TempMapData[7 - j][i];
                                        playerData[j][i] = TempPlayerData[7 - i][j];
                                    }
                                }
                                //プレイヤー位置検索
                                for (int i = 0; i < 8; i++) {
                                    for (int j = 0; j < 8; j++) {
                                        if (playerData[i][j] != 0) {
                                            //座標に戻す
                                            player.x = j * 128 + 64;
                                            player.y = i * 128 + 127;
                                            playerData[i][j] = 0;
                                        }
                                        TempPlayerData[i][j] = 0;
                                    }
                                }

                                //黒ブロック

                                //配列の引数を求める 
                                {
                                    for (int i = 0; i < BlackCount[StageCnt]; i++) {
                                        int bxr = (black[i].x) / 128;
                                        int byr = (black[i].y) / 128;
                                        TempBlackData[byr][bxr] = 1;
                                    }
                                }
                                //配列に回転させた位置保存
                                for (int i = 0; i < 8; i++) {
                                    for (int j = 0; j < 8; j++) {
                                        blackData[j][i] = TempBlackData[7 - i][j];
                                    }
                                }

                                //ブロック位置検索
                                {

                                    int n = 0;
                                    for (int i = 0; i < 8; i++) {
                                        for (int j = 0; j < 8; j++) {
                                            if (blackData[i][j] != 0) {
                                                //座標に戻す
                                                black[n].x = j * 128 + 64;
                                                black[n].y = i * 128 + 64;
                                                blackData[i][j] = 0;
                                                n++;
                                            }
                                            TempBlackData[i][j] = 0;
                                        }
                                    }
                                }

                                //特殊行動終わり
                                if (SpecialAction)SpecialAction = false;

                                //初期化
                                player.rotationFlag = false;
                                player.rotationTimer = 0;
                            }

                        }



                    }
                    //リトライ
                    //if (EdgeInput & PAD_INPUT_B){
                    //    for (int i = 0; i < 8; i++) {
                    //        for (int j = 0; j < 8; j++) {
                    //            MapData[i][j] = RetryData[i][j];
                    //        }
                    //    }
                    //}

                    //マップデータコピー
                    for (int i = 0; i < 8; i++) {
                        for (int j = 0; j < 8; j++) {
                            TempMapData[i][j] = MapData[i][j];

                        }
                    }
                    //マップ変更
                    //(次のステージフラグ・リセットフラグとブラックアウトが半分終わっていたら)
                    if (NextStage == true || ResetStage == true && ColorMax) {

                        //プレイヤー初期化
                        playerInit();

                        if (player.damageFlag) {
                            player.damageFlag = false;
                            player.damageTimer = 0;
                        }

                        //黒ブロックリセット
                        /*
                        for (int i = 0; i < BlackCount[StageCnt]; i++) {//ブロックのある数だけ
                            black[i].x = 0;
                            black[i].y = 0;
                            black[i].onGround = false;
                            black[i].speed = 0;
                            black[i].spawn = false;
                            black[i].No = 0;
                        }
                        */
                        blackInit();
                        //黒ブロック設置
                        for (int i = 0; i < BlackCount[StageCnt]; i++) {//ブロックのある数だけ
                            black[i].x = 128 * BlackPos[StageCnt][i].x + CHIP_SIZE / 2;  //真ん中に
                            black[i].y = 128 * BlackPos[StageCnt][i].y + CHIP_SIZE / 2;
                            black[i].spawn = true;
                            black[i].No = i;
                        }

                        stageSet();

                        //ステージずれ補正
                        if (NextStage)NextStage = false;
                        if (ResetStage)ResetStage = false;

                        //特殊行動終わり
                        if (SpecialAction)SpecialAction = false;
                    }
                }
                //背景描画
                // キャラクター
                //      画像を決める
                int playerHandle = {};//描画する画像
                int divisionTime = 10;  //割る時間
                //左右
                if (player.speedX == 0 && player.speedY == 0)playerHandle = PlayerAnime[0];
                if (player.speedX > 0 || player.speedX < 0)playerHandle = PlayerAnime[walkNo[player.animeTime / divisionTime % 4]];

                //ジャンプ踏ん張り
                if (player.jumpTimer) {
                    playerHandle = PlayerAnime[animeJumpImage[player.jumpTimer / 5]];
                }
                //落下
                if (player.fallTimer) playerHandle = PlayerAnime[36 - 1];

                //反転・回転
                if (player.inversionFlag)playerHandle = PlayerAnime[animeInversion[player.inversionTimer / 10 % 5]];
                if (player.rotationFlag) playerHandle = PlayerAnime[animeRotation[player.rotationTimer / 10 % 5]];
                if (player.damageFlag) playerHandle = PlayerAnime[animeDamage[player.damageTimer / 4 % 3]];


                //描画
                //プレイヤー

                if (player.rotationFlag) {//反転・回転画像がずれているので調整
                    if (!player.Xflip) {//右
                        DrawGraph(player.x - 62 + stageoffsetX, player.y - 115 + stageoffsetY, playerHandle, TRUE);
                    }
                    else {
                        DrawTurnGraph(player.x - 67 + stageoffsetX, player.y - 115 + stageoffsetY, playerHandle, TRUE);
                    }
                }
                else if (player.inversionFlag) {
                    if (!player.Xflip) {//右
                        DrawGraph(player.x - 64 + stageoffsetX, player.y - 115 + stageoffsetY, playerHandle, TRUE);
                    }
                    else {
                        DrawTurnGraph(player.x - 64 + stageoffsetX, player.y - 115 + stageoffsetY, playerHandle, TRUE);
                    }
                }
                else if (player.fallTimer || player.jumpTimer) {//落下中
                    if (!player.Xflip) {//右
                        DrawGraph(player.x - 64 + stageoffsetX, player.y - 115 + stageoffsetY, playerHandle, TRUE);
                    }
                    else {
                        DrawTurnGraph(player.x - 64 + stageoffsetX, player.y - 115 + stageoffsetY, playerHandle, TRUE);
                    }
                }
                else {//その他プレイヤー
                    if (!player.Xflip) {//右
                        DrawGraph(player.x - 68 + stageoffsetX, player.y - 115 + stageoffsetY, playerHandle, TRUE);
                    }
                    else {
                        DrawTurnGraph(player.x - 61 + stageoffsetX, player.y - 115 + stageoffsetY, playerHandle, TRUE);
                    }
                }

                //黒いボックス
                for (int i = 0; i < BlackCount[StageCnt]; i++) {
                    if (black[i].spawn) {
                        DrawGraph(black[i].x - CHIP_SIZE / 2 + stageoffsetX, black[i].y - CHIP_SIZE / 2 + stageoffsetY, moveblock[0], TRUE);
                    }
                }

                //UI
                float scale = 1.65;
                int Y = 0;
                //回転
                int X = CHIP_SIZE * 11 + 70;
                DrawExtendGraph(X, Y, X + (CHIP_SIZE * scale), Y + (CHIP_SIZE * scale), UI_Rotation, TRUE);
                //反転
                X = CHIP_SIZE * 13 + 40;
                DrawExtendGraph(X, Y, X + (CHIP_SIZE * scale), Y + (CHIP_SIZE * scale), UI_Inversion, TRUE);


                //セレクト
                scale = 1.45f;
                Y = CHIP_SIZE * 7 - 2;
                X = 90;
                DrawExtendGraph(X, Y, X + (CHIP_SIZE * scale), Y + (CHIP_SIZE * scale), UI_Select, TRUE);

                //リセット
                scale = 1.65f;
                Y = CHIP_SIZE * 6 + 100;
                X = 1600;
                DrawExtendGraph(X, Y, X + (CHIP_SIZE * scale), Y + (CHIP_SIZE * scale), UI_Reset, TRUE);

                /*
                X = 80;
                Y = CHIP_SIZE * 6+70;
                DrawExtendGraph(X, Y, X + (CHIP_SIZE * scale), Y + (CHIP_SIZE * scale), UI_Select, TRUE);
                X = 1600;
                DrawExtendGraph(X, Y, X + (CHIP_SIZE * scale), Y + (CHIP_SIZE * scale), UI_Reset, TRUE);
                */





                //debug

                 /*
                DrawCircle(player.x+stageoffsetX, player.y + stageoffsetY, 5, GetColor(1,1,1),1);
                DrawFormatString(0, 1*12, GetColor(0,0,0), "StageCntは %d です", StageCnt);

                DrawBox(player.x - CHAR_SIZE / 2+stageoffsetX, player.y - CHAR_SIZE-playerOffsetY + stageoffsetY, player.x + CHAR_SIZE / 2+stageoffsetX, player.y + stageoffsetY, GetColor(1, 0, 1), 0.1f);
                for (int i = 0; i < BlackCount[StageCnt]; i++) {
                    DrawCircle(black[i].x+stageoffsetX, black[i].y + stageoffsetY, 5, GetColor(1, 1, 1), 1);
                    DrawBox(black[i].x - CHIP_SIZE / 2+stageoffsetX, black[i].y - CHIP_SIZE / 2 + stageoffsetY, black[i].x + CHIP_SIZE / 2 + stageoffsetX, black[i].y + CHIP_SIZE / 2 + stageoffsetY,
                        GetColor(1, 0, 0), 0);
                }


                if(!isBlackStop())DrawFormatString(0, 43, GetColor(1, 1, 0), "playerSpeedXは %f です", player.speedX);
                for (int i = 0; i < BlackCount[StageCnt]; i++) {
                    DrawFormatString(0, i * 20+100, GetColor(0, 0, 0), "黒ブロックは %d", black[i].onGround);
                }

                DrawFormatString(0, 10 * 12, GetColor(0, 0, 0), "BlackOut %d です", BlackOut);

                DrawFormatString(0, 11 * 12, GetColor(0, 0, 0), "BlackTimer %d です", BlackTimer);

                DrawFormatString(0, 14 * 12, GetColor(0, 0, 0), "WhiteOut %d です", WhiteOut);

                DrawFormatString(0, 15 * 12, GetColor(0, 0, 0), "WhiteTimer %d です", WhiteTimer);
                DrawFormatString(0, 17 * 12, GetColor(0, 0, 0), "SpecialAction %d です", SpecialAction);



                DrawFormatString(0, 18 * 12, GetColor(0, 0, 0), "damageFlag %d です", player.damageFlag);
                DrawFormatString(0, 19 * 12, GetColor(0, 0, 0), "damageTimer %d です", player.damageTimer);

                */
                //アニメ用の変数加算
                player.animeTime++;

                //回転・反転
                if (player.inversionFlag) {
                    player.inversionTimer++;
                    if (player.inversionTimer > MAX_INVERSION_TIME) {
                        player.inversionTimer = MAX_INVERSION_TIME;
                    }
                }
                if (player.rotationFlag) {
                    player.rotationTimer++;
                    if (player.rotationTimer > MAX_ROTATION_TIME) {
                        player.rotationTimer = MAX_ROTATION_TIME;
                    }
                }

                //ダメージ
                if (player.damageFlag) {
                    player.damageTimer++;
                    //if (player.damageTimer > MAX_DAMAGE_TIME) {繰り返すので不必要
                    //    player.damageTimer = MAX_DAMAGE_TIME;
                    //}
                }


                break;

            }

            case 7://クリア初期化

                clearText[0]= LoadGraph("画像/clearText.png");
                clearText[1]= LoadGraph("画像/clearText_0.png");//説明
                clearText[2]= LoadGraph("画像/clearText_1.png");//次へ
                clearText[3]= LoadGraph("画像/clearText_2.png");//もう一回
                clearText[4]= LoadGraph("画像/clearText_3.png");//戻る

                clearIcon[0]= LoadGraph("画像/clearIcon_0.png");
                clearIcon[1]= LoadGraph("画像/clearIcon_1.png");
                clearIcon[2]= LoadGraph("画像/clearIcon_2.png");

                stopBGM();

                scrollCnt = 0;
                ClearStage = false;

                gamemode++;
            case 8://クリア処理
                
                ClearSc();
                break;

            }

            //ブラックアウトホワイトアウト
               //ブラックホワイト描画
            BlackOutRender();
            WhiteOutRender();

            //ブラックホワイト加算
            BlackOutTimer();
            WhiteOutTimer();

        }
        // 画面の更新
        ScreenFlip();
        NowSc += 3;

    }

    // 終了
    return 0;
}

//HACK: 触った

// キャラクタをマップとの当たり判定を考慮しながら移動する
int CharMove(Player& player,float Size)
{
    float Dummy = 0.0F;
    float hsize;

    // 半分のサイズを算出
    hsize = Size * 0.5F;

    //上下チェック
    {
        //最大速度チェック
        if (player.speedY > MAX_SPEED_Y)
            player.speedY = MAX_SPEED_Y;
        if (player.speedY < -MAX_SPEED_Y)
            player.speedY = -MAX_SPEED_Y;

        //加算
        float oldY = player.y;
        player.y += player.speedY;
        float deltaY = player.y - oldY;//上下かどうかに使用

        player.onGround = false;    //フラグ消す

        //当たり判定
        //下
        if (deltaY > 0)
        {
            if (isFloor(player.x, player.y, hsize))//ここのサイズは後々2倍にしてもいいかも??
            {
                //補正
                player.y -= fmodf(player.y, CHIP_SIZE) + 0.025f;
                player.speedY = player.speedY < 0.0f ? player.speedY : 0.0f;
                player.onGround = true; //地面フラグ
            }

            //黒ブロック
            if (isFloorBlack(player.x, player.y, hsize))//めり込んだプレイヤー座標
            {
                //補正
                //Block black = whoBlack(player.x, player.y);
                //下にブロックがあるのがわかっているので、下のマスの真ん中
                float blackCenterY = ((int)player.y / CHIP_SIZE) * CHIP_SIZE + CHIP_SIZE / 2;
                if(player.y > blackCenterY)//押しつぶされている
                {
                    PlaySoundFile("サウンド/damege.mp3", DX_PLAYTYPE_BACK);

                    resetStage();
                }
                if (player.y < blackCenterY) {//足場が黒ブロック
                    player.y -= fmodf(player.y, CHIP_SIZE) + 0.025f;
                    player.speedY = player.speedY < 0.0f ? player.speedY : 0.0f;
                    player.onGround = true; //地面フラグ
                }
            }

            //ちょっとめりこんでいるのでちょっと上の所で判定取る
            //黒ブロックで挟まれた場合を取るため
            if (isFloorBlack(player.x, player.y-1, hsize))
            {
                //補正
                //Block black = whoBlack(player.x, player.y);
                //下にブロックがあるのがわかっているので、下のマスの真ん中
                float blackCenterY = ((int)player.y / CHIP_SIZE) * CHIP_SIZE + CHIP_SIZE / 2;
                if (player.y > blackCenterY)//押しつぶされている
                {
                    PlaySoundFile("サウンド/damege.mp3", DX_PLAYTYPE_BACK);

                    resetStage();
                }
                if (player.y < blackCenterY) {//足場が黒ブロック
                    player.y -= fmodf(player.y, CHIP_SIZE) + 0.025f;
                    player.speedY = player.speedY < 0.0f ? player.speedY : 0.0f;
                    player.onGround = true; //地面フラグ
                }
            }

            if (isFloorNeedle(player.x, player.y, hsize))//マップチップ的にはとげか
            {
                float needleY = (((int)player.y / CHIP_SIZE)*CHIP_SIZE)+needleOffset;
                if (needleY <= player.y) {
                    //補正
                    //player.y -= fmodf(player.y, CHIP_SIZE) + 0.025f;
                    //player.y -= fmodf(needleY, CHIP_SIZE) + 0.025f;
                    player.y -= fmodf(needleY, CHIP_SIZE) + 0.025f;
                    player.speedY = player.speedY < 0.0f ? player.speedY : 0.0f;
                    //player.onGround = true; //地面フラグ

                    PlaySoundFile("サウンド/damege.mp3", DX_PLAYTYPE_BACK);

                    player.damageFlag = true;
                    resetStage();
                }
            }
        }

        //上
        if (deltaY < 0)
        {
            if (isCeiling(player.x , player.y - Size-playerOffsetY, hsize))//ここもサイズは後々2倍にしてもいいかも??
            {
                //補正
                float y = player.y - Size-playerOffsetY;//ここも2倍
                player.y += CHIP_SIZE - fmodf(y, CHIP_SIZE);
                player.speedY = 0.0f;
            }

            //黒ブロック
            if (isCeilingBlack(player.x, player.y - Size - playerOffsetY, hsize))
            {
                //補正
                float y = player.y - hsize - playerOffsetY;//ここも2倍
                //player.y += CHIP_SIZE - fmodf(y, CHIP_SIZE);
                player.speedY = player.speedY > 0.0f ? player.speedY : 0.0f;

                PlaySoundFile("サウンド/damege.mp3", DX_PLAYTYPE_BACK);

                resetStage();
            }
            if (isCeilingNeedle(player.x, player.y - Size - playerOffsetY, hsize))//ここもサイズは後々2倍にしてもいいかも??
            {
                float needleY = (((int)player.y / CHIP_SIZE) * CHIP_SIZE)+CHIP_SIZE - needleOffset;
                if (needleY >= player.y) {
                    //補正
                    float y = player.y - Size;//ここも2倍
                    player.y += CHIP_SIZE-needleOffset - fmodf(needleY, CHIP_SIZE);
                    player.speedY = player.speedY > 0.0f ? player.speedY : 0.0f;

                    PlaySoundFile("サウンド/damege.mp3", DX_PLAYTYPE_BACK);

                    player.damageFlag = true;
                    resetStage();
                }
            }
        }
    }

    // 左右チェック
    {
        //最大速度チェック
        if (player.speedX > MAX_SPEED_X)
            player.speedX=MAX_SPEED_X;
        if (player.speedX < -MAX_SPEED_X)
            player.speedX=-MAX_SPEED_X;

        //加算
        float oldX = player.x;
        player.x += player.speedX;
        float deltaX = player.x - oldX;//左右かどうかに使用


        //当たり判定
        //右
        if (deltaX > 0) {
            //壁
            if (isWall(player.x + hsize, player.y, Size))//右が壁か
            {
                //補正
                float hoseiX = player.x + hsize;//TODO:hsizeはのちのち当たり判定の右に
                player.x -= fmodf(hoseiX, CHIP_SIZE ) + 0.025f;//ちょっと離したものを足す
                player.speedX = 0.0f;
                //壁フラグを立てたりしてもいいかも？
            }
            if (isWall(player.x + hsize+1, player.y, Size))//ちょっと乗ることがあるので阻止
            {
                //補正
                player.x -= 1 + 0.025f;//ちょっと離したものを足す
                player.speedX = 0.0f;
                //壁フラグを立てたりしてもいいかも？
            }
            //黒ブロック
            if (isBlack(player.x  + hsize, player.y))
            {
                //補正
                float hoseiX = player.x + hsize;//TODO:hsizeはのちのち当たり判定の右に
                player.x -= fmodf(hoseiX, CHIP_SIZE) + 0.025f;//ちょっと離したものを足す
                player.speedX = 0.0f;
            }
            //とげブロック
            if (isWallNeedle(player.x + hsize, player.y,Size))
            {
                //とげの当たり判定に当たったときのみ補正(上下で当たってなくて横に入力すると補正されるので)
                float needleYDown = ((int)player.y / CHIP_SIZE) * CHIP_SIZE + needleOffset;
                float needleYUp = ((int)player.y / CHIP_SIZE) * CHIP_SIZE*2 - needleOffset;
                if (needleYUp <= player.y&&needleYUp>=player.y-Size|| needleYDown <= player.y&&needleYDown>=player.y-Size) {
                    //補正
                    float hoseiX = player.x + hsize;//TODO:hsizeはのちのち当たり判定の右に
                    player.x -= fmodf(hoseiX, CHIP_SIZE) + 0.025f;//ちょっと離したものを足す
                    player.speedX = 0.0f;
                    PlaySoundFile("サウンド/damege.mp3", DX_PLAYTYPE_BACK);

                    player.damageFlag = true;
                    resetStage();

                }
            }
            
        }

        //左
        if (deltaX < 0) {
            //壁
            if (isWall(player.x - hsize , player.y, Size))//左が壁か
            {
                //補正
                float hoseiX = player.x - hsize;//TODO:hsizeはのちのち当たり判定の右に
                player.x += CHIP_SIZE-fmodf(hoseiX, CHIP_SIZE) + 0.025f;//ちょっと離したものを足す
                player.speedX = 0.0f;
                //壁フラグを立てたりしてもいいかも？
            }
            if (isWall(player.x + hsize - 1, player.y, Size))//ちょっと乗ることがあるので阻止
            {
                //補正
                player.x += 1 + 0.025f;//ちょっと離したものを足す
                player.speedX = 0.0f;
                //壁フラグを立てたりしてもいいかも？
            }
            //黒ブロック
            if (isBlack(player.x  - hsize , player.y))
            {
                //補正
                float hoseiX = player.x - hsize;//TODO:hsizeはのちのち当たり判定の右に
                player.x += CHIP_SIZE - fmodf(hoseiX, CHIP_SIZE) + 0.025f;//ちょっと離したものを足す
                player.speedX = 0.0f;
            }
            //壁
            if (isWallNeedle(player.x - hsize, player.y, Size))//左が壁か
            {
                //とげの当たり判定に当たったときのみ補正(上下で当たってなくて横に入力すると補正されるので)
                float needleYDown = ((int)player.y / CHIP_SIZE) * CHIP_SIZE + needleOffset; 
                float needleYUp = ((int)player.y / CHIP_SIZE) * CHIP_SIZE * 2 - needleOffset;
                if (needleYUp <= player.y && needleYUp >= player.y - Size || needleYDown <= player.y && needleYDown >= player.y - Size) {
                    //補正
                    float hoseiX = player.x - hsize;//TODO:hsizeはのちのち当たり判定の右に
                    player.x += CHIP_SIZE - fmodf(hoseiX, CHIP_SIZE) + 0.025f;//ちょっと離したものを足す
                    player.speedX = 0.0f;
                    PlaySoundFile("サウンド/damege.mp3", DX_PLAYTYPE_BACK);


                    player.damageFlag = true;
                    resetStage();
                }
                //壁フラグを立てたりしてもいいかも？
            }
        }
    }

    //その他の当たり判定
    {
        //ゴールの当たり判定
        if (!player.damageFlag&&GetChipParam(player.x, player.y) == 1)
        {
            BlackOut = true;
            ClearStage = true;
            //if (StageCnt == 19) {
            //    gamemode = 3;
            //}
            //else {
            //    NextStage = true;
            //    StageCnt++;
            //}
        }

        if (ClearStage && ColorMax) {
            PlaySoundFile("サウンド/clear.wav", DX_PLAYTYPE_BACK); //効果音
            gamemode = 7;
        }
    }


    
    //時間の加算
    if (!player.onGround && player.speedY < 0) {//上昇中
        player.jumpTimer++;

        //最大値調整
        if (player.jumpTimer > MAX_JUMPTIME)
            player.jumpTimer = MAX_JUMPTIME;
    }

    if (!player.onGround && player.speedY >= 0) {//落下中
        player.fallTimer++; 
        player.jumpTimer = 0;
    }

    //時間変数の管理
    if (player.onGround) {
        player.fallTimer = 0;
        player.jumpTimer = 0;
    }

    // 終了
    return 0;
}

bool isBlack(float x,float y)
{


    if (BlackCount[StageCnt] == 0)return false;
    for (int i = 0; i < BlackCount[StageCnt]; i++) {
        if (black[i].spawn) {
            int bx = (int)black[i].x / CHIP_SIZE;
            int by = (int)black[i].y / CHIP_SIZE;
            int px = (int)x / CHIP_SIZE;
            int py = (int)y / CHIP_SIZE;

            if (bx == px && by == py) {
                return true;
            }
        }
    }

    return false;
}

Block& whoBlack(float x, float y)
{

    if (BlackCount[StageCnt] != 0) {
        for (int i = 0; i < BlackCount[StageCnt]; i++) {
            if (black[i].spawn) {
                int bx = (int)black[i].x / CHIP_SIZE;
                int by = (int)black[i].y / CHIP_SIZE;
                int px = (int)x / CHIP_SIZE;
                int py = (int)y / CHIP_SIZE;

                if (bx == px && by == py) {
                    return black[i];
                }
            }
        }
    }

}
//ToDo:  BlackMove

//HACK: 触った
//// ブロックをマップとの当たり判定を考慮しながら移動する
int BlackMove(Block& black,float Size)
{
    float Dummy = 0.0F;
    float hsize;

    // 半分のサイズ
    hsize = Size * 0.5F;

    // 加算
    black.y+= black.speed;
            
    //下チェック
    {
        //最大速度チェック
        if (black.speed > MAX_BLOCK_SPEED_Y)
            black.speed = MAX_BLOCK_SPEED_Y;

        // 真ん中下のさらに5ドット下
        if (BlackMapHitCheck(black.x, black.y + hsize+5, &Dummy, &black.speed) == 4)
        {
            black.speed = 0;   //重力消滅
            black.y = ((int)black.y/CHIP_SIZE)*CHIP_SIZE+CHIP_SIZE/2;    //補正(移動先で配列配置に似た形)
            black.onGround = true;     //着地フラグ
            int x = black.x / CHIP_SIZE;
            int y = black.y / CHIP_SIZE;
        }
        else if (blackHitBlack(black))
        {
            black.onGround = true;
        }
        else if (BlackMapHitCheck(black.x, black.y + hsize + 5, &Dummy, &black.speed) == 2)//マップチップ的にはとげか
        {
            black.speed = 0;   //重力消滅
            black.y = ((int)black.y / CHIP_SIZE) * CHIP_SIZE + CHIP_SIZE / 2;    //補正(移動先で配列配置に似た形)
            black.onGround = true;     //着地フラグ
            int x = black.x / CHIP_SIZE;
            int y = black.y / CHIP_SIZE;
            //DrawFormatString(0, 15 * 2, GetColor(0, 0, 0), "black needle itai", StageCnt);
        }
        else
        {
            black.onGround = false;
        }
        
    }
    // 終了
    return 0;
}

//黒い箱同士の当たり判定
bool blackHitBlack(Block& Black)
{
    for (int i = BlackCount[StageCnt]; i > 0; i--) {//相手(下から判定取ってる)(下が着地しているか見るので)
        int x0 = (int)Black.x / CHIP_SIZE;
        int x1 = (int)black[i].x / CHIP_SIZE;
        int y0 = (int)Black.y / CHIP_SIZE;
        int y1 = (int)black[i].y / CHIP_SIZE;
        if (Black.No == black[i].No)continue;//自分なら
        if (x0 != x1)continue;//同じｘ軸じゃない
        if (Black.y > black[i].y)continue;//自分が上
        if (!black[i].onGround)continue;//相手が着地している

            if (black[i].y - Black.y <= CHIP_SIZE) {//間がチップサイズ以下で
                //float hoseiY = ((black[i].y - CHIP_SIZE / 2) - (Black.y + CHIP_SIZE / 2));
                //if (hoseiY < 0)hoseiY *= -1;
                Black.y = black[i].y - CHIP_SIZE;// hoseiY;
                Black.onGround = true;
                Black.speed = 0.0f;
                return true;
            }
    }
    return false;
}

//TODO: BlackMapHitCheck


//HACK::触った
int BlackMapHitCheck(float X, float Y,
    float* MoveX, float* MoveY)
{
    // 移動量を足す
    float afX = X + *MoveX;
    float afY = Y + *MoveY;

    // 当たり判定のあるブロックに当たっているかチェック   (移動先に普通ブロックがあるか)
    if (GetChipParam(afX, afY) == 0)return 4;//普通ブロック
    if (GetChipParam(afX, afY) == 2)return 2;//とげ
    
    return 0;
}

// マップチップの値を取得する関数
int GetChipParam(float X, float Y)
{
    int x, y;

    // 整数値へ変換
    x = (int)X / CHIP_SIZE;
    y = (int)Y / CHIP_SIZE;

    // マップからはみ出ていたら 0 を返す
    if (x >= MAP_WIDTH || y >= MAP_HEIGHT || x < 0 || y < 0) return 0;

    // 指定の座標に該当するマップの情報を返す
    return MapData[y][x];
}