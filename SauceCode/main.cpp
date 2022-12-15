#include "DxLib.h"
#include "iostream"
#define SCREEN_WIDTH     (1920)                          // ��ʂ̉���
#define SCREEN_HEIGHT    (1080)                          // ��ʂ̏c��
#define CHIP_SIZE        (128)                           // ��̃`�b�v�̃T�C�Y
#define MAP_WIDTH        (SCREEN_WIDTH / CHIP_SIZE)      // �}�b�v�̉���
#define MAP_HEIGHT       (SCREEN_HEIGHT / CHIP_SIZE)     // �}�b�v�̏c��

#define MAP_N 8
#define MAP_M 8

#define G                (0.3F)                         // �L�����Ɋ|����d�͉����x
#define JUMP_POWER       (10.0F)                         // �L�����̃W�����v��
#define SPEED            (5.0F)                         // �L�����̈ړ��X�s�[�h
#define MAX_SPEED_X      (5.0F)                         // �L������X�ő�X�s�[�h
#define MAX_SPEED_Y      (12.0F)                         // �L������Y�ő�X�s�[�h
#define MAX_BLOCK_SPEED_Y      (10.0F)                         // �L������Y�ő�X�s�[�h
#define DECCEL           (1.0F)                         // �L�����̌����X�s�[�h

#define MAX_JUMPTIME     (14.0F)

#define MAX_ROTATION_TIME  4*10
#define MAX_INVERSION_TIME 4*10
#define MAX_DAMAGE_TIME 4*10

#define MAX_BLACKOUT_TIME 30
#define MAX_WHITEOUT_TIME 30


#define CHAR_SIZE        (64)                           // �v���C���[�̃T�C�Y


#define BLOCK_MAX 9 //1�X�e�[�W�̍ő�u���b�N��

// �}�b�v�f�[�^
int MapData[MAP_N][MAP_M] ={};
//�v���C���[�̈ʒu��ۑ�����z��
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


//���u���b�N�̈ʒu��ۑ�����z��
int blackData[MAP_N][MAP_M] = {};
//�X�e�[�W���Ƃ̃u���b�N��
const int BlackCount[20] = {
    0,1,1,7,4,
    3,7,0,6,9,
    0,4,0,8,0,
    0,1,1,0,3
};
//���u���b�N�̏����}�X
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



//�ꎞ�I�ɕێ����Ă����}�b�v�f�[�^
int TempMapData[MAP_N][MAP_M] =
{
    0
};
int TempPlayerData[MAP_N][MAP_M] =
{
    0
};
int TempBlackData[MAP_N][MAP_M] = {};

//���g���C�p�}�b�v�f�[�^�i�����ʒu�j
int RetryData[MAP_N][MAP_M] =
{
    0
};

//TODO: �ϐ��u����

//��]�ɕK�v�ȕϐ�
int n;  
int m;
int cnt;

//�����蔻��p
struct Box {
    float left;
    float right;
    float top;
    float bottom;
};

//�v���C���[�p
//float PlX = 256, PlY = 1024;            // �v���C���[�̍��W(���S���W)   //TODO:�����������̎�������x�����ق��������񂶂�Ȃ���
//float PlDownSp;            // �v���C���[�̗������x
//char PlJumpFlag;           // �v���C���[���W�����v�����A�̃t���O

struct Player {
    float x, y; //�ʒu
    float speedX,speedY;    //���x        //VECTOR2�ɂ��Ă���
    bool onGround;  //���n�t���O

    int animeTime;//�摜�Ɏg�p����b��
    bool Xflip;//�����Ă������(�E:false�A��:true)


    bool rotationFlag;   //��]�t���O   true�ɂ���Ύ��Ԃ������A��]���I������玞��0�ɂȂ�
    bool inversionFlag;   //���]�t���O�@true�ɂ���Ύ��Ԃ������A��]���I������玞��0�ɂȂ�
    bool damageFlag;    //�_���[�W�t���O


    //���Ԃ��摜�Ɏg���Ă���
    int fallTimer;  //��������
    int jumpTimer;  //�W�����v����
    int damageTimer;//�_���[�W����
    int rotationTimer;//��]����
    int inversionTimer;//���]����
    int clearTimer;//�N���A����

};

Player player = {};

//�u���b�N�p
//float blockX, blockY; //�u���b�N���W�i���S�j
//float BlackDownSp;
//bool blockGround;       //�u���b�N���n�ʂɂ��Ă��邩
int moveblock[1];

//�u���b�N�\����
struct Block {
    float x, y; //�ʒu
    float speed; //���x
    bool onGround;  //���n�t���O
    bool spawn; //���݂��邩   ������Ƃ��Ɏg������(���݂��Ȃ��͂��̂��̂Ɠ����蔻������Ȃ��悤��)
    int No;//����(���u���b�N���m�̔���Ɏg��)
};

Block black[BLOCK_MAX] = {};


int Input, EdgeInput;      // ���͏��
int FrameStartTime;        // �U�O�e�o�r�Œ�p�A���ԕۑ��p�ϐ�



//�X�e�[�W�ύX
bool NextStage = false;         //TODO:�@���������ŏ��������Ă�ƌ�ŏ��������Y�ꂻ��
bool ResetStage = false;
bool ClearStage = false;    //�N���A�������A�g���܂킵�Ńu���b�N�A�E�g�Ɏg���Ă��肷��B
bool ReturnStage = false;
int StageCnt = 0;

int WhiteTimer = 0;//�o�ߎ���
int BlackTimer = 0;//�o�ߎ���

bool WhiteOut = false;//�t���O
bool BlackOut = false;//�t���O

bool ColorMax = false;//�u���b�N�A�E�g�z���C�g�A�E�g�Ɏg��(�u���b�N�A�E�g�z���C�g�A�E�g�������Ŋ���)

int BlackBack;//�摜
int WhiteBack;//�摜

bool SpecialAction = false;
//����s��(��]�E���]�E���Z�b�g)�̎��ɑ��̓���s�����o���Ȃ��悤��
//true�ɂ���Ƒ��̓���s����ړ����o���Ȃ��Ȃ�


//�X�e�[�W���炵�̈ʒu�␳
const float stageoffsetX= SCREEN_WIDTH / 4 - 64;
const float stageoffsetY= (SCREEN_HEIGHT -CHIP_SIZE*8)/2;//�]����/2(�^�񒆂�)
//const float stageoffsetX= 0;


//�v���C���[�A�j���[�V����
int PlayerAnime[56];//�ҋ@

//�A�j���[�V�����̏���
int walkNo[4] = { 7,8,9,8 };
//���񒣂�̉摜�ꏊ
int animeJumpImage[4] = { 29,30,31,32 };
//���]�̉摜
int animeInversion[5] = {22,23,24,25,26};
//��]�̉摜
int animeRotation[5] = {15,16,17,18,19};
//�_���[�W�̉摜
int animeDamage[3] = {43,44,45};
//�N���A���[�V�����̉摜
int animeClear[7] = { 50,51,52,53,54,55,56 };
//�A�j���̎�ޕʂ̐�
int animeType[8] = { 1,3,5,5,4,1,3,7 };

//float playerOffsetX = CHAR_SIZE;
float playerOffsetY = 20;



//UI
int UI_Inversion;
int UI_Rotation;
int UI_Reset;
int UI_Select;


//��ʐ���
int NowSc = 1;
int Title;

int gamemode = 1;


//HACK:�T�E���h�֌W

int titleBGM;
int selectBGM;
int gameBGM;

int rotationSe = LoadSoundMem("�T�E���h/rotation.mp3");



//�v���C���[�̉�]�p
int plxr, plyr;

//�X�e�[�W�摜
int StageImg[10];


//�w�i�摜
int back;
int frame;

//�Z���N�g�w�i�`��
int selectbg;
int selection[20];
int selectImg[5];
int offset=64;

int scrollCnt = 0;

//�N���A�w�i�摜
int clearText[5];
int clearIcon[3];

//HACK: �G����
//�Ƃ��̓����蔻��p
float needleOffset = 25;


// �}�b�v�`�b�v�̒l���擾����֐�
int GetChipParam(float X, float Y);

// �L�����N�^���}�b�v�Ƃ̓����蔻����l�����Ȃ���ړ�����֐�
int CharMove(Player& player, float Size);
//int CharMove(float* X, float* Y, float* DownSP,
//    float MoveX, float MoveY, float Size, char* JumpFlag);

//TODO:   PlayerClearRender
void playerClearRender()
{
    int playerHandle = {};//�`�悷��摜
    int X1 = 400;
    int Y1 = 790;
    int devisionTime = 4;
    playerHandle = PlayerAnime[animeClear[player.clearTimer / 10 % 6]];
    DrawGraph(X1, Y1, playerHandle, TRUE);
    player.clearTimer++;
}


//���ʃu���b�N����Ԃ��֐�
bool isHit(float x, float y)
{
    return(GetChipParam(x, y) == 0);    //���ʃu���b�N��0�ɂ��Ă��邩���ʊO�ł��O�Ŏ��Ă�
}

//�ǂ����肷��֐�
bool isWall(float x, float y, float height)//�z��͊�_���^�񒆉��
{
    for (; height > 0; height -= CHIP_SIZE)
    {
        const float yPos = y - height;//�}�b�v�`�b�v1���ł����ꍇ�B�������ɏ��X�Ɍ��Ă���(��Ō��炵�Ă���̂�)
        //��ʊO�Ȃ�
        if (yPos < 0)      continue;
        if (yPos > SCREEN_HEIGHT) continue;

        if (isHit(x, yPos))
            return true;
    }
    return isHit(x, y);
}

//�V�䂩���肷��֐�
bool isCeiling(float x, float y, float width)
{
    for (; width > 0; width -= CHIP_SIZE)
    {
        const float left = x - width;
        const float right = x + width;

        // �G���A�`�F�b�N
        if (left < 0)       continue;
        if (right >= SCREEN_WIDTH) continue;

        if (isHit(left, y))  return true;
        if (isHit(right, y)) return true;
    }
    return isHit(x, y);
}

//�������肷��֐�
bool isFloor(float x, float y, float width)
{
    for (; width > 0; width -= CHIP_SIZE)       // width��CHIP_SIZE�����炵�Ă���
    {
        const float left = x - width;
        const float right = x + width;

        // �G���A�`�F�b�N
        if (left < 0)       continue;
        if (right >= SCREEN_WIDTH) continue;

        if (isHit(left, y))  return true;   // ���[����
        if (isHit(right, y)) return true;   // �E�[����
    }
    return isHit(x, y);                     // �Ō�ɐ^�񒆂Ŕ���
}


//���u���b�N
//���̏ꏊ���z��I�Ɍ��ē����}�X��
bool isBlack(float x,float y);

//�V�䂩���肷��֐�
bool isCeilingBlack(float x, float y, float width)
{
    for (; width > 0; width -= CHIP_SIZE)
    {
        const float left = x - width;
        const float right = x + width;

        // �G���A�`�F�b�N
        if (left < 0)       continue;
        if (right >= SCREEN_WIDTH) continue;

        if (isBlack(left, y))  return true;
        if (isBlack(right, y)) return true;
    }
    return isBlack(x, y);
}

//�������肷��֐�
bool isFloorBlack(float x, float y, float width)
{
    for (; width > 0; width -= CHIP_SIZE)       // width��CHIP_SIZE�����炵�Ă���
    {
        const float left = x - width;
        const float right = x + width;

        // �G���A�`�F�b�N
        if (left < 0)       continue;
        if (right >= SCREEN_WIDTH) continue;

        if (isBlack(left, y))  return true;   // ���[����
        if (isBlack(right, y)) return true;   // �E�[����
    }
    return isBlack(x, y);                     // �Ō�ɐ^�񒆂Ŕ���
}


//HACK: �G����

//
//�Ƃ��u���b�N����Ԃ��֐�
bool isHitNeedle(float x, float y)
{
    return(GetChipParam(x, y) == 2);    //���ʃu���b�N��0�ɂ��Ă��邩���ʊO�ł��O�Ŏ��Ă�
}

//�ǂ��g�Q�����肷��֐�
bool isWallNeedle(float x, float y, float height)//�z��͊�_���^�񒆉��
{
    for (; height > 0; height -= CHIP_SIZE)
    {
        const float yPos = y - height;//�}�b�v�`�b�v1���ł����ꍇ�B�������ɏ��X�Ɍ��Ă���(��Ō��炵�Ă���̂�)
        //��ʊO�Ȃ�
        if (yPos < 0)      continue;
        if (yPos > SCREEN_HEIGHT) continue;

        if (isHitNeedle(x, yPos))
            return true;
    }
    return isHitNeedle(x, y);
}

//���E���Ƃ������肷��֐�
bool isNeedle(float x, float y, float height)//�z��͊�_���^�񒆉��
{
    for (; height > 0; height -= CHIP_SIZE)
    {
        const float yPos = y - height;//�}�b�v�`�b�v1���ł����ꍇ�B�������ɏ��X�Ɍ��Ă���(��Ō��炵�Ă���̂�)
        //��ʊO�Ȃ�
        if (yPos < 0)      continue;
        if (yPos > SCREEN_HEIGHT) continue;

        if (isHitNeedle(x, yPos))
            return true;
    }
    return isHitNeedle(x, y);
}
//�V�䂪�Ƃ������肷��֐�
bool isCeilingNeedle(float x, float y, float width)
{
    for (; width > 0; width -= CHIP_SIZE)
    {
        const float left = x - width;
        const float right = x + width;

        // �G���A�`�F�b�N
        if (left < 0)       continue;
        if (right >= SCREEN_WIDTH) continue;

        if (isHitNeedle(left, y))  return true;
        if (isHitNeedle(right, y)) return true;
    }
    return isHitNeedle(x, y);
}

//�����Ƃ������肷��֐�
bool isFloorNeedle(float x, float y, float width)
{
    for (; width > 0; width -= CHIP_SIZE)       // width��CHIP_SIZE�����炵�Ă���
    {
        const float left = x - width;
        const float right = x + width;

        // �G���A�`�F�b�N
        if (left < 0)       continue;
        if (right >= SCREEN_WIDTH) continue;

        if (isHitNeedle(left, y))  return true;   // ���[����
        if (isHitNeedle(right, y)) return true;   // �E�[����
    }
    return isHitNeedle(x, y);                     // �Ō�ɐ^�񒆂Ŕ���
}
//

//�����蔻��p
bool hitCheck(Box box1,Box box2)
{
    if (box1.right < box2.left) return false;
    if (box1.left > box2.right) return false;
    if (box1.bottom < box2.top) return false;
    if (box1.top > box2.bottom) return false;

    return true;
}


//���̃}�X�ɔ���Ă��鍕�u���b�N��Ԃ�
Block& whoBlack(float x, float y);

//�u���b�N���m�̓����蔻��
bool blackHitBlack(Block& Black);

//�u���b�N�ƃ}�b�v�Ƃ̓����蔻����l�����Ȃ���ړ�����֐�
int BlackMove(Block& black,float Size);

// �A�N�V�����T���v���v���O�������C���֐�
int ActMain(void);

//�u���b�N�p
int BlackMapHitCheck(float X, float Y, float* MoveX, float* MoveY);

//�S�u���b�N�����n���Ă��邩
bool isBlackStop() {
    int blackGround = 0;//���n�ς݃u���b�N
    if (black[0].spawn == true)//��ڂ̃u���b�N������Ȃ�
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

//���Z�b�g�֐�
void resetStage() {
    ResetStage = true;
    BlackOut = true;
    SpecialAction = true;
}

//�u���b�N�z���C�g�֐�

//�ϐ��̏�����
void BlackWhiteInit() {

    WhiteTimer = 0;
    BlackTimer = 0;

    WhiteOut = false;
    BlackOut = false;

    ColorMax = false;
}

//�摜�̃��[�h
void BlackWhiteLoad() {
    //�u���b�N�A�E�g�z���C�g�A�E�g
    BlackBack = LoadGraph("�摜/black.png");
    WhiteBack = LoadGraph("�摜/white.png");
}

//�`��
void BlackOutRender()
{
    if (BlackOut) {
        int alpha = BlackTimer * (255 / MAX_BLACKOUT_TIME) * 3;
        if (alpha >= 255)alpha = 255;

        SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
        DrawGraph(0, 0, BlackBack, true);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

        //DrawFormatString(0, 9 * 12, GetColor(0, 0, 0), "alpha %d �ł�", alpha);
        if (ColorMax && BlackTimer == 0)//�����߂��ĕ\�����I�������
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

        //DrawFormatString(0, 9 * 12, GetColor(0, 0, 0), "alpha %d �ł�", alpha);
        if (ColorMax && WhiteTimer == 0)//�����߂��ĕ\�����I�������
        {
            ColorMax = false;
            WhiteOut = false;
        }
    }
}

//���Ԋ֌W(�`��̌���)
void BlackOutTimer()//���Ԋ֌W
{
    //�u���b�N�A�E�g�z���C�g�A�E�g(����Ȃ�t���O�𗧂Ă�)
    if (BlackOut) {
        //���Z
        if (!ColorMax)BlackTimer++;
        else BlackTimer--;//�`�悷�鎞�Ԕ����߂�����

        //�t���O
        if (BlackTimer == MAX_BLACKOUT_TIME / 2) {//�����Ȃ�
            ColorMax = true;
        }
        //����
        //if (BlackTimer > MAX_BLACKOUT_TIME) {//�ő�)
        //    BlackTimer = MAX_BLACKOUT_TIME;
        //}
        if (BlackTimer < 0) {//�ő�
            BlackTimer = 0;
        }
    }
}
void WhiteOutTimer() {
    if (WhiteOut) {
        //���Z
        if (!ColorMax)WhiteTimer++;
        else WhiteTimer--;//�`�悷�鎞�Ԕ����߂�����

        //�t���O
        if (WhiteTimer == MAX_WHITEOUT_TIME / 2) {//�����Ȃ�
            ColorMax = true;
        }
        //����
        //if (WhiteTimer > MAX_WHITEOUT_TIME) {//�ő�)
        //    WhiteTimer = MAX_WHITEOUT_TIME;
        //}
        if (WhiteTimer < 0) {//�ő�
            WhiteTimer = 0;
        }
    }
}




//�������֐�
void playerInit()
{
    // �v���C���[�̗������x��������
    player.speedY = 0.0F;
    player.speedX = 0.0f;
    // �W�����v���t���O��|��
    player.onGround = false;
    //�v���C���[�̃A�j���̏�����
    player.animeTime = 0;
    //�v���C���[�̍��E
    player.Xflip = false;
    //�v���C���[����s���t���O
    player.rotationFlag = false;
    player.inversionFlag = false;
    player.damageFlag = false;

    //�v���C���[�̎��Ԃ̏�����
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
    // �c�w���C�u�����̏�����
    if (DxLib_Init() == -1) return -1;

    //�摜�̃��[�h
    //�v���C���[�摜
    LoadDivGraph("�摜/player.png", 56, 7, 8, 128, 128, PlayerAnime);


    //�u���b�N�z���C�g�̏�����
    BlackWhiteInit();
    BlackWhiteLoad();

    ActMain();

    // �c�w���C�u�����̌�n��
    DxLib_End();
    // �I��
    return 0;
}

void TitleSc(void)
{
    //��ʐ���
    DrawGraph(0, 0, Title, true);

    if (CheckHitKeyAll(DX_CHECKINPUT_ALL)) {
        if (!BlackOut) {
            PlaySoundFile("�T�E���h/decision.wav", DX_PLAYTYPE_BACK); //���ʉ�
        }
        BlackOut = true;
        ClearStage = true;

    }
    if (ClearStage&&ColorMax) {
        StopSoundMem(titleBGM);
        gamemode++;//�Z���N�g��������
        ClearStage = false;
    }
}

void SelectSc(void)
{
       DrawGraph(0, 0, back, true);

       int oldNum=scrollCnt / 5;//�Â����l
        if (CheckHitKey(KEY_INPUT_A) && scrollCnt > 0) {
            scrollCnt--;

            //StageCnt--; //�X�e�[�W�J�E���g���炷
            //NextStage = true;
        }
        if (CheckHitKey(KEY_INPUT_D) && scrollCnt < 19*5) {
            scrollCnt++;
            

            //StageCnt++; //�X�e�[�W�J�E���g���₷
            //NextStage = true;
        }

        if (scrollCnt <= 0)scrollCnt = 0;
        if (scrollCnt >= 19*5)scrollCnt = 19*5;
        int Num = scrollCnt / 5;
        if (oldNum != Num) {
            PlaySoundFile("�T�E���h/cursor.wav", DX_PLAYTYPE_BACK); //���ʉ�
        }
        //DrawRotaGraph(300, SCREEN_HEIGHT / 2, 1, 0, selecticon[1], true); //1�̕`��H�H�H�H

        int selectX = 400;
        for (int i = 0; i < 5; i++) {
            
            if (i + Num > 19)break;
                DrawRotaGraph(selectX + 300 * i, SCREEN_HEIGHT / 2, 1, 0, selection[i + Num], true); //������6���̂ݕ`��
                //DrawFormatString(0, 20 * i, GetColor(0, 0, 0), "���[�񂱂�͕ϐ�i = %d", i);
                if (i == 0)
                {
                    DrawRotaGraph(selectX + 300 * i, SCREEN_HEIGHT / 2, 1.3, 0, selection[i + Num], true); //������6���̂ݕ`��

                }
        }

        //���
        if(Num !=0)
        DrawRotaGraph(70,              SCREEN_HEIGHT / 2, 1, 0, selectImg[2], true);//�E
        if(Num !=19)
        DrawRotaGraph(SCREEN_WIDTH - 70,SCREEN_HEIGHT / 2, 1, 0, selectImg[3], true);//��

        //�^�C�g��
        DrawRotaGraph(500, 150, 1.3f, 0, selectImg[0], true);

        //����
        DrawRotaGraph(SCREEN_WIDTH/2, 1010, 1, 0, selectImg[1], true);

        //UI
        DrawRotaGraph(100,980, 1,0, selectImg[4], true);
        

        //�^�C�g����ʑJ��&�u���b�N�A�E�g
        if (CheckHitKey(KEY_INPUT_Z)) { //0key
            BlackOut = true;
            ReturnStage = true;//�g���܂킵
            //StopSoundFile();
        }
        if (ReturnStage && ColorMax) {
            gamemode=1;
            ReturnStage = false;
        }

        //�Q�[����ʑJ��&�u���b�N�A�E�g
    if (CheckHitKey(KEY_INPUT_SPACE)) { //0key
        if (!ClearStage) {
            PlaySoundFile("�T�E���h/decision.wav", DX_PLAYTYPE_BACK); //���ʉ�
        }
        BlackOut = true;
        ClearStage = true;//�g���܂킵
        //StopSoundFile();
    }
    
    if (ClearStage && ColorMax) {
        StageCnt = Num;
        gamemode++;
        StopSoundMem(selectBGM);
        ClearStage = false;
    }
   
}

void ClearSc()//�N���A
{
    DrawGraph(0, 0, back, true);

    int oldNum= scrollCnt / 5;
    if (CheckHitKey(KEY_INPUT_W) && scrollCnt > 0) {
        scrollCnt--;

        //StageCnt--; //�X�e�[�W�J�E���g���炷
        //NextStage = true;
    }
    if (CheckHitKey(KEY_INPUT_S) && scrollCnt < 2 * 5) {
        scrollCnt++;
        //StageCnt++; //�X�e�[�W�J�E���g���₷
        //NextStage = true;
    }

    //if (scrollCnt <= 0)scrollCnt = 0;
    //if (scrollCnt >= 3 * 5)scrollCnt = 3 * 5;
    int Num = scrollCnt / 5;
    if (Num < 0)Num = 0;
    if (Num > 2)Num = 2;

    if(oldNum!=Num)
        PlaySoundFile("�T�E���h/cursor.wav", DX_PLAYTYPE_BACK); //���ʉ�
    //�e�L�X�g
    VECTOR2 pos[3] = {
        {100 * 10,   100 * 5.5},
        {100 * 10+55,100 * 7+40},
        {100 * 10,   100 * 8.5}
    };
    float scale[3] = { 1.3f,1.3f,1.3f };
    scale[Num] *= 1.3f;

    DrawRotaGraph(pos[0].x, pos[0].y, scale[0], 0, clearText[2], true); ////����
    DrawRotaGraph(pos[1].x, pos[1].y, scale[1], 0, clearText[3], true); ////�������
    DrawRotaGraph(pos[2].x, pos[2].y, scale[2], 0, clearText[4], true); ////�߂�

    //�A�C�R��
    VECTOR2 pos2[3] = {
        {100 * 6.5,   100 * 5.5},
        {100 * 6.5,100 * 7 },
        {100 * 6.5,   100 * 8.5}
    };
    DrawRotaGraph(pos2[0].x, pos2[0].y, 1.3f, 0, clearIcon[0], true); //������6���̂ݕ`��
    DrawRotaGraph(pos2[1].x, pos2[1].y, 1.3f, 0, clearIcon[1], true); //������6���̂ݕ`��
    DrawRotaGraph(pos2[2].x, pos2[2].y, 1.3f, 0, clearIcon[2], true); //������6���̂ݕ`��
        

    //�^�C�g��
    DrawRotaGraph(930, 300, 1.3f, 0, clearText[0], true);

    //����
    DrawRotaGraph(1500, 1010, 1.0f, 0, clearText[1], true);

    //�v���C���[
    playerClearRender();

    //DrawFormatString(0, 15 * 2, GetColor(0, 0, 0), "�X�e�[�Wnumber%d", StageCnt);
    if (CheckHitKey(KEY_INPUT_SPACE)) { //0key
        BlackOut = true;
        ClearStage = true;//�g���܂킵
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
    // �`���𗠉�ʂɃZ�b�g
    SetDrawScreen(DX_SCREEN_BACK);

    // ���������M����҂��Ȃ�
    SetWaitVSyncFlag(FALSE);


    //�^�C�g���摜
    //LoadDivGraph("�摜/title.png", 1, 1, 1, 1920, 1080, Title);

    //�X�e�[�W�摜
    LoadDivGraph("�摜/mapchip.png", 4, 4, 1, 128, 128, StageImg);
    //�u���b�N
    LoadDivGraph("�摜/moveblock.png", 1, 1, 1, 128, 128, moveblock);

    //�w�i�摜
    back = LoadGraph("�摜/back.png");
    frame = LoadGraph("�摜/frame.png");



    //UI
    UI_Inversion = LoadGraph("�摜/UI_L.png");
    UI_Rotation = LoadGraph("�摜/UI_K.png");
    UI_Reset = LoadGraph("�摜/UI_X.png");
    UI_Select = LoadGraph("�摜/UI_Z.png");

    //�v���C���[�̏�����
    playerInit();
    player.x = 256;
    player.y = 1000;


    NextStage = false;
    ResetStage = false;

    SpecialAction = false;

    ////�X�e�[�W������
    //for (int i = 0; i < 8; i++) {
    //    for (int j = 0; j < 8; j++) {
    //        MapData[i][j] = Stage1[i][j];
    //        RetryData[i][j] = Stage1[i][j];
    //
    //    }
    //}


     //TODO: �u���b�N������
     //BlackDownSp = 0.0F;
     //���u���b�N�̏�����
    blackInit();


    // ���͏�Ԃ̏�����
    Input = 0;
    EdgeInput = 0;




    // �U�O�e�o�r�Œ�p�A���ԕۑ��p�ϐ������݂̃J�E���g�l�ɃZ�b�g
    FrameStartTime = GetNowCount();

    // ���C�����[�v�J�n�A�d�r�b�L�[�ŊO�ɏo��
    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {
        // ��ʂ̃N���A
        ClearDrawScreen();

        // �P/�U�O�b���܂ő҂�
        while (GetNowCount() - FrameStartTime < 1000 / 60) {}
        // ���݂̃J�E���g�l��ۑ�
        FrameStartTime = GetNowCount();
        {
            switch (gamemode)
            {
            case 1://�^�C�g��������

                //���[�h
                titleBGM = LoadSoundMem("�T�E���h/title.mp3");
                Title = LoadGraph("�摜/title.png");

                stopBGM();

                PlaySoundMem(titleBGM, DX_PLAYTYPE_LOOP, TRUE);//���o��
                //��deinit�ō폜���Ȃ��Ƃ����Ȃ��Ƃ����邩��

                //StopSoundMem(titleBGM);

                gamemode++;
                break;
            case 2://�^�C�g��
                TitleSc();
                
                break;

            case 3://�Z���N�g������
                //���[�h
                selectBGM = LoadSoundMem("�T�E���h/select.mp3");

                stopBGM();

                PlaySoundMem(selectBGM, DX_PLAYTYPE_LOOP, TRUE);//���o��

                //���[�h
                selectbg = LoadGraph("�摜/select.png");
                selection[0] = LoadGraph("�摜/�X�e�[�W1.png");
                selection[1] = LoadGraph("�摜/�X�e�[�W2.png");
                selection[2] = LoadGraph("�摜/�X�e�[�W3.png");
                selection[3] = LoadGraph("�摜/�X�e�[�W4.png");
                selection[4] = LoadGraph("�摜/�X�e�[�W5.png");
                selection[5] = LoadGraph("�摜/�X�e�[�W6.png");
                selection[6] = LoadGraph("�摜/�X�e�[�W7.png");
                selection[7] = LoadGraph("�摜/�X�e�[�W8.png");
                selection[8] = LoadGraph("�摜/�X�e�[�W9.png");
                selection[9] = LoadGraph("�摜/�X�e�[�W10.png");
                selection[10] = LoadGraph("�摜/�X�e�[�W11.png");
                selection[11] = LoadGraph("�摜/�X�e�[�W12.png");
                selection[12] = LoadGraph("�摜/�X�e�[�W13.png");
                selection[13] = LoadGraph("�摜/�X�e�[�W14.png");
                selection[14] = LoadGraph("�摜/�X�e�[�W15.png");
                selection[15] = LoadGraph("�摜/�X�e�[�W16.png");
                selection[16] = LoadGraph("�摜/�X�e�[�W17.png");
                selection[17] = LoadGraph("�摜/�X�e�[�W18.png");
                selection[18] = LoadGraph("�摜/�X�e�[�W19.png");
                selection[19] = LoadGraph("�摜/�X�e�[�W20.png");

                selectImg[0]= LoadGraph("�摜/selectText.png");  //�^�C�g��
                selectImg[1]= LoadGraph("�摜/selectText_0.png");//����
                selectImg[2]= LoadGraph("�摜/arrowLeft.png"); //���
                selectImg[3]= LoadGraph("�摜/arrowRight.png");//���E
                selectImg[4]= LoadGraph("�摜/UI_Z.png");//UI


                ReturnStage = false;

                //������
                scrollCnt = 0;

                gamemode++;

            case 4:
                SelectSc();
                break;

            case 5://���C��������

                gameBGM = LoadSoundMem("�T�E���h/game.mp3");

                stopBGM();

                PlaySoundMem(gameBGM, DX_PLAYTYPE_LOOP, TRUE);//���o��

                playerInit();

                if (player.damageFlag) {
                    player.damageFlag = false;
                    player.damageTimer = 0;
                }

                blackInit();
                //���u���b�N�ݒu
                for (int i = 0; i < BlackCount[StageCnt]; i++) {//�u���b�N�̂��鐔����
                    black[i].x = 128 * BlackPos[StageCnt][i].x + CHIP_SIZE / 2;  //�^�񒆂�
                    black[i].y = 128 * BlackPos[StageCnt][i].y + CHIP_SIZE / 2;
                    black[i].spawn = true;
                    black[i].No = i;
                }

                stageSet();

                //�X�e�[�W����␳
                if (NextStage)NextStage = false;
                if (ResetStage)ResetStage = false;

                //����s���I���
                if (SpecialAction)SpecialAction = false;


                gamemode++;

            case 6://���C��
            {
                //�w�i�`��
                DrawGraph(0, 0, back, true);
                DrawGraph(389, 0, frame, true);//�t���[���`��
                    

                // �v���C���[�̈ړ�����
                {
                    if (isBlackStop()) {
                        if (!SpecialAction) {
                            if (CheckHitKey(KEY_INPUT_A)) {//��
                                player.speedX -= SPEED;
                                player.Xflip = true;
                            }
                            else if (CheckHitKey(KEY_INPUT_D)) {//�E
                                player.speedX += SPEED;
                                player.Xflip = false;
                            }
                            else {//�����Ă��Ȃ�
                                if (player.speedX > 0) {
                                    player.speedX -= DECCEL;
                                    if (player.speedX < 0)player.speedX = 0.0f;
                                }
                                if (player.speedX < 0) {
                                    player.speedX += DECCEL;
                                    if (player.speedX > 0)player.speedX = 0.0f;
                                }
                            }

                            // ���E�̈ړ�������
                            /*
                            switch (Input & (PAD_INPUT_LEFT | PAD_INPUT_RIGHT))
                            {
                            case PAD_INPUT_LEFT:player.speedX -= SPEED;  player.Xflip = true; break;
                            case PAD_INPUT_RIGHT:player.speedX += SPEED; player.Xflip = false; break;
                            default://�����ĂȂ�
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
                            // �n�ɑ��������Ă���ꍇ�̂݃W�����v�{�^��(�{�^���P or �y�L�[)������
                        }
                    }

                    if (!player.damageFlag) {
                        // ��������
                        player.speedY += G;
                    }

                    //���E�������ςŉ�]����Ɖ����Ȃ��Ă��ړ�����̂�
                    if (!isBlackStop())player.speedX = 0.0f;

                    //�W�����v
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

                    //// �������x���ړ��ʂɉ�����
                    //MoveY = PlDownSp;

                    // �ړ��ʂɊ�Â��ăL�����N�^�̍��W���ړ�
                    CharMove(player, CHAR_SIZE);

                    //��ʊO�␳(���߂ɕԂ�)(����������̂�)
                    float offset = 0.025f;
                    if (player.x - CHAR_SIZE / 2 < 0)player.x = CHAR_SIZE / 2 + offset;//��
                    if (player.x + CHAR_SIZE / 2 > CHIP_SIZE * 8.0f)player.x = CHIP_SIZE * 8.0f - CHAR_SIZE / 2 - offset;//�E
                    if (player.y - CHAR_SIZE < 0)player.y = CHAR_SIZE + offset;//��
                    if (player.y > CHIP_SIZE * 8.0f)player.y = CHIP_SIZE * 8.0f - offset;//��

                    //CharMove(&PlX, &PlY, &PlDownSp, MoveX, MoveY, CHAR_SIZE, &PlJumpFlag);


                }

                // �u���b�N�̈ړ�����
                {
                    float BMoveX, BMoveY;

                    // �ړ��ʂ̏�����
                    BMoveX = 0.0F;
                    BMoveY = 0.0F;

                    for (int i = 0; i < BlackCount[StageCnt]; i++) {
                        if (!black[i].onGround) {  //�����Ă��Ȃ��Ȃ�
                            // ��������
                            black[i].speed += G * 0.9;

                            // �������x���ړ��ʂɉ����� //����K�v?
                            //BMoveY = BlackDownSp
                        }
                        //�ړ��ʂɊ�Â��ăL�����N�^�̍��W���ړ�
                        BlackMove(black[i], CHIP_SIZE);
                    }
                }

                //HACK:����

                // �}�b�v�̕`��
                {
                    int i, j;
                    for (i = 0; i < 8; i++)
                    {
                        for (j = 0; j < 8; j++)
                        {
                            // ���΃`�b�v�̕`��
                            if (MapData[i][j] == 0)
                            {
                                //DrawBox(j * CHIP_SIZE, i * CHIP_SIZE,
                                //    j * CHIP_SIZE + CHIP_SIZE, i * CHIP_SIZE + CHIP_SIZE,
                                //    GetColor(255, 255, 155), TRUE);
                                DrawGraph(j * CHIP_SIZE + stageoffsetX, i * CHIP_SIZE + stageoffsetY, StageImg[0], TRUE);
                                //DrawBox(j * CHIP_SIZE+stageoffsetX, i* CHIP_SIZE + stageoffsetY, j * CHIP_SIZE+CHIP_SIZE + stageoffsetX, i * CHIP_SIZE + CHIP_SIZE + stageoffsetY, GetColor(1, 1, 1), 0);

                            }
                            //�S�[���`�b�v�̕`��
                            if (MapData[i][j] == 1)
                            {
                                //DrawBox(j * CHIP_SIZE, i * CHIP_SIZE,
                                //    j * CHIP_SIZE + CHIP_SIZE, i * CHIP_SIZE + CHIP_SIZE,
                                //    GetColor(100, 255, 255), TRUE);
                                DrawGraph(j * CHIP_SIZE + stageoffsetX, i * CHIP_SIZE + stageoffsetY, StageImg[1], TRUE);


                            }
                            //�Ƃ��̕`��
                            if (MapData[i][j] == 2)
                            {
                                //HACK: �G����

    /*                       //      DrawBox(j * CHIP_SIZE, i * CHIP_SIZE,
                                     j * CHIP_SIZE + CHIP_SIZE, i * CHIP_SIZE + CHIP_SIZE,
                                     GetColor(100, 155, 255), TRUE);*/
                                DrawGraph(j * CHIP_SIZE + stageoffsetX, i * CHIP_SIZE + stageoffsetY, StageImg[2], TRUE);

                                //DrawCircle(j*CHIP_SIZE+CHIP_SIZE/2 + stageoffsetX, i* CHIP_SIZE+CHIP_SIZE/2 + stageoffsetY, 5, GetColor(1, 0, 1), 0);
                                //DrawBox(j* CHIP_SIZE + stageoffsetX, i* CHIP_SIZE + stageoffsetY+needleOffset, j *CHIP_SIZE+ CHIP_SIZE + stageoffsetX, i *CHIP_SIZE+ CHIP_SIZE+ stageoffsetY-needleOffset,
                                //GetColor(1, 0.6f, 1), 0);
                            }
                            //�u���b�N�̕`��
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


                //�X�e�[�W���Z�b�g�t���O
                //if (!SpecialAction&&player.onGround && Input & PAD_INPUT_X) {
                if (!SpecialAction && player.onGround && CheckHitKey(KEY_INPUT_X)) {
                    resetStage();

                }

                //�߂�
                if (!SpecialAction && player.onGround && CheckHitKey(KEY_INPUT_Z)) {
                    ReturnStage = true;
                    BlackOut = true;
                }
                if (ReturnStage && ColorMax) {
                    gamemode = 3;
                }

                //�X�e�[�W�̏���
                if (NowSc != 2) {
                    if (isBlackStop()) {

                        //�}�b�v�̔��]
                        //if (!SpecialAction&&player.onGround&&EdgeInput & PAD_INPUT_A) {//���]�t���O
                        if (!SpecialAction && player.onGround && CheckHitKey(KEY_INPUT_L)) {//���]�t���O
                            //�v���C���[
                            player.speedX = 0.0f;
                            //�t���O����
                            player.inversionFlag = true;

                            SpecialAction = true;

                            PlaySoundFile("�T�E���h/inversion.mp3", DX_PLAYTYPE_BACK); //���ʉ�
                        }

                        //�A�j���[�V�����I���Ȃ�
                        if (player.inversionFlag && player.inversionTimer >= MAX_INVERSION_TIME) {

                            WhiteOut = true;
                            if (ColorMax) {//�^�����Ȃ�

                                //�z��̈��������߂�
                                plxr = (player.x) / 128;
                                plyr = (player.y) / 128;
                                TempPlayerData[plyr][plxr] = 1;
                                for (int i = 0; i < 8; i++) {
                                    for (int j = 0; j < 8; j++) {
                                        MapData[i][j] = TempMapData[i][7 - j];
                                        playerData[i][j] = TempPlayerData[i][7 - j];
                                    }
                                }
                                //�v���C���[�ʒu����
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

                                //���u���b�N

                                //�z��̈��������߂�
                                {
                                    for (int i = 0; i < BlackCount[StageCnt]; i++) {
                                        int bxr = (black[i].x) / 128;
                                        int byr = (black[i].y) / 128;
                                        TempBlackData[byr][bxr] = 1;
                                    }
                                }
                                //�z��ɉ�]�������ʒu�ۑ�
                                for (int i = 0; i < 8; i++) {
                                    for (int j = 0; j < 8; j++) {
                                        blackData[i][j] = TempBlackData[i][7 - j];
                                    }
                                }
                                //�u���b�N�ʒu����
                                {
                                    int n = 0;
                                    for (int i = 0; i < 8; i++) {
                                        for (int j = 0; j < 8; j++) {
                                            if (blackData[i][j] != 0) {
                                                //���W�ɖ߂�
                                                black[n].x = j * 128 + 64;
                                                black[n].y = i * 128 + 64;
                                                blackData[i][j] = 0;
                                                n++;
                                            }
                                            TempBlackData[i][j] = 0;
                                        }
                                    }
                                }

                                //����s���I���
                                if (SpecialAction)SpecialAction = false;

                                //������
                                player.inversionFlag = false;
                                player.inversionTimer = 0;
                            }

                        }

                        //90�x��]
                        //if (!SpecialAction&&player.onGround&&EdgeInput & PAD_INPUT_B) {//������
                        if (!SpecialAction && player.onGround && CheckHitKey(KEY_INPUT_K)) {//������
                            //�v���C���[
                            player.speedX = 0.0f;
                            //�t���O����
                            player.rotationFlag = true;//�`��p

                            SpecialAction = true;

                            PlaySoundFile("�T�E���h/rotation.mp3", DX_PLAYTYPE_BACK); //���ʉ�
                        }

                        //�A�j���[�V�����I���Ȃ�
                        if (player.rotationFlag && player.rotationTimer >= MAX_ROTATION_TIME) {//�ő厞��


                            WhiteOut = true;
                            if (ColorMax) {//�^�����Ȃ�
                            //�z��̈��������߂� 
                                plxr = (player.x) / 128;
                                plyr = (player.y) / 128;
                                TempPlayerData[plyr][plxr] = 1;
                                //�z��ɉ�]�������ʒu�ۑ�
                                for (int i = 0; i < 8; i++) {
                                    for (int j = 0; j < 8; j++) {
                                        MapData[i][j] = TempMapData[7 - j][i];
                                        playerData[j][i] = TempPlayerData[7 - i][j];
                                    }
                                }
                                //�v���C���[�ʒu����
                                for (int i = 0; i < 8; i++) {
                                    for (int j = 0; j < 8; j++) {
                                        if (playerData[i][j] != 0) {
                                            //���W�ɖ߂�
                                            player.x = j * 128 + 64;
                                            player.y = i * 128 + 127;
                                            playerData[i][j] = 0;
                                        }
                                        TempPlayerData[i][j] = 0;
                                    }
                                }

                                //���u���b�N

                                //�z��̈��������߂� 
                                {
                                    for (int i = 0; i < BlackCount[StageCnt]; i++) {
                                        int bxr = (black[i].x) / 128;
                                        int byr = (black[i].y) / 128;
                                        TempBlackData[byr][bxr] = 1;
                                    }
                                }
                                //�z��ɉ�]�������ʒu�ۑ�
                                for (int i = 0; i < 8; i++) {
                                    for (int j = 0; j < 8; j++) {
                                        blackData[j][i] = TempBlackData[7 - i][j];
                                    }
                                }

                                //�u���b�N�ʒu����
                                {

                                    int n = 0;
                                    for (int i = 0; i < 8; i++) {
                                        for (int j = 0; j < 8; j++) {
                                            if (blackData[i][j] != 0) {
                                                //���W�ɖ߂�
                                                black[n].x = j * 128 + 64;
                                                black[n].y = i * 128 + 64;
                                                blackData[i][j] = 0;
                                                n++;
                                            }
                                            TempBlackData[i][j] = 0;
                                        }
                                    }
                                }

                                //����s���I���
                                if (SpecialAction)SpecialAction = false;

                                //������
                                player.rotationFlag = false;
                                player.rotationTimer = 0;
                            }

                        }



                    }
                    //���g���C
                    //if (EdgeInput & PAD_INPUT_B){
                    //    for (int i = 0; i < 8; i++) {
                    //        for (int j = 0; j < 8; j++) {
                    //            MapData[i][j] = RetryData[i][j];
                    //        }
                    //    }
                    //}

                    //�}�b�v�f�[�^�R�s�[
                    for (int i = 0; i < 8; i++) {
                        for (int j = 0; j < 8; j++) {
                            TempMapData[i][j] = MapData[i][j];

                        }
                    }
                    //�}�b�v�ύX
                    //(���̃X�e�[�W�t���O�E���Z�b�g�t���O�ƃu���b�N�A�E�g�������I����Ă�����)
                    if (NextStage == true || ResetStage == true && ColorMax) {

                        //�v���C���[������
                        playerInit();

                        if (player.damageFlag) {
                            player.damageFlag = false;
                            player.damageTimer = 0;
                        }

                        //���u���b�N���Z�b�g
                        /*
                        for (int i = 0; i < BlackCount[StageCnt]; i++) {//�u���b�N�̂��鐔����
                            black[i].x = 0;
                            black[i].y = 0;
                            black[i].onGround = false;
                            black[i].speed = 0;
                            black[i].spawn = false;
                            black[i].No = 0;
                        }
                        */
                        blackInit();
                        //���u���b�N�ݒu
                        for (int i = 0; i < BlackCount[StageCnt]; i++) {//�u���b�N�̂��鐔����
                            black[i].x = 128 * BlackPos[StageCnt][i].x + CHIP_SIZE / 2;  //�^�񒆂�
                            black[i].y = 128 * BlackPos[StageCnt][i].y + CHIP_SIZE / 2;
                            black[i].spawn = true;
                            black[i].No = i;
                        }

                        stageSet();

                        //�X�e�[�W����␳
                        if (NextStage)NextStage = false;
                        if (ResetStage)ResetStage = false;

                        //����s���I���
                        if (SpecialAction)SpecialAction = false;
                    }
                }
                //�w�i�`��
                // �L�����N�^�[
                //      �摜�����߂�
                int playerHandle = {};//�`�悷��摜
                int divisionTime = 10;  //���鎞��
                //���E
                if (player.speedX == 0 && player.speedY == 0)playerHandle = PlayerAnime[0];
                if (player.speedX > 0 || player.speedX < 0)playerHandle = PlayerAnime[walkNo[player.animeTime / divisionTime % 4]];

                //�W�����v���񒣂�
                if (player.jumpTimer) {
                    playerHandle = PlayerAnime[animeJumpImage[player.jumpTimer / 5]];
                }
                //����
                if (player.fallTimer) playerHandle = PlayerAnime[36 - 1];

                //���]�E��]
                if (player.inversionFlag)playerHandle = PlayerAnime[animeInversion[player.inversionTimer / 10 % 5]];
                if (player.rotationFlag) playerHandle = PlayerAnime[animeRotation[player.rotationTimer / 10 % 5]];
                if (player.damageFlag) playerHandle = PlayerAnime[animeDamage[player.damageTimer / 4 % 3]];


                //�`��
                //�v���C���[

                if (player.rotationFlag) {//���]�E��]�摜������Ă���̂Œ���
                    if (!player.Xflip) {//�E
                        DrawGraph(player.x - 62 + stageoffsetX, player.y - 115 + stageoffsetY, playerHandle, TRUE);
                    }
                    else {
                        DrawTurnGraph(player.x - 67 + stageoffsetX, player.y - 115 + stageoffsetY, playerHandle, TRUE);
                    }
                }
                else if (player.inversionFlag) {
                    if (!player.Xflip) {//�E
                        DrawGraph(player.x - 64 + stageoffsetX, player.y - 115 + stageoffsetY, playerHandle, TRUE);
                    }
                    else {
                        DrawTurnGraph(player.x - 64 + stageoffsetX, player.y - 115 + stageoffsetY, playerHandle, TRUE);
                    }
                }
                else if (player.fallTimer || player.jumpTimer) {//������
                    if (!player.Xflip) {//�E
                        DrawGraph(player.x - 64 + stageoffsetX, player.y - 115 + stageoffsetY, playerHandle, TRUE);
                    }
                    else {
                        DrawTurnGraph(player.x - 64 + stageoffsetX, player.y - 115 + stageoffsetY, playerHandle, TRUE);
                    }
                }
                else {//���̑��v���C���[
                    if (!player.Xflip) {//�E
                        DrawGraph(player.x - 68 + stageoffsetX, player.y - 115 + stageoffsetY, playerHandle, TRUE);
                    }
                    else {
                        DrawTurnGraph(player.x - 61 + stageoffsetX, player.y - 115 + stageoffsetY, playerHandle, TRUE);
                    }
                }

                //�����{�b�N�X
                for (int i = 0; i < BlackCount[StageCnt]; i++) {
                    if (black[i].spawn) {
                        DrawGraph(black[i].x - CHIP_SIZE / 2 + stageoffsetX, black[i].y - CHIP_SIZE / 2 + stageoffsetY, moveblock[0], TRUE);
                    }
                }

                //UI
                float scale = 1.65;
                int Y = 0;
                //��]
                int X = CHIP_SIZE * 11 + 70;
                DrawExtendGraph(X, Y, X + (CHIP_SIZE * scale), Y + (CHIP_SIZE * scale), UI_Rotation, TRUE);
                //���]
                X = CHIP_SIZE * 13 + 40;
                DrawExtendGraph(X, Y, X + (CHIP_SIZE * scale), Y + (CHIP_SIZE * scale), UI_Inversion, TRUE);


                //�Z���N�g
                scale = 1.45f;
                Y = CHIP_SIZE * 7 - 2;
                X = 90;
                DrawExtendGraph(X, Y, X + (CHIP_SIZE * scale), Y + (CHIP_SIZE * scale), UI_Select, TRUE);

                //���Z�b�g
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
                DrawFormatString(0, 1*12, GetColor(0,0,0), "StageCnt�� %d �ł�", StageCnt);

                DrawBox(player.x - CHAR_SIZE / 2+stageoffsetX, player.y - CHAR_SIZE-playerOffsetY + stageoffsetY, player.x + CHAR_SIZE / 2+stageoffsetX, player.y + stageoffsetY, GetColor(1, 0, 1), 0.1f);
                for (int i = 0; i < BlackCount[StageCnt]; i++) {
                    DrawCircle(black[i].x+stageoffsetX, black[i].y + stageoffsetY, 5, GetColor(1, 1, 1), 1);
                    DrawBox(black[i].x - CHIP_SIZE / 2+stageoffsetX, black[i].y - CHIP_SIZE / 2 + stageoffsetY, black[i].x + CHIP_SIZE / 2 + stageoffsetX, black[i].y + CHIP_SIZE / 2 + stageoffsetY,
                        GetColor(1, 0, 0), 0);
                }


                if(!isBlackStop())DrawFormatString(0, 43, GetColor(1, 1, 0), "playerSpeedX�� %f �ł�", player.speedX);
                for (int i = 0; i < BlackCount[StageCnt]; i++) {
                    DrawFormatString(0, i * 20+100, GetColor(0, 0, 0), "���u���b�N�� %d", black[i].onGround);
                }

                DrawFormatString(0, 10 * 12, GetColor(0, 0, 0), "BlackOut %d �ł�", BlackOut);

                DrawFormatString(0, 11 * 12, GetColor(0, 0, 0), "BlackTimer %d �ł�", BlackTimer);

                DrawFormatString(0, 14 * 12, GetColor(0, 0, 0), "WhiteOut %d �ł�", WhiteOut);

                DrawFormatString(0, 15 * 12, GetColor(0, 0, 0), "WhiteTimer %d �ł�", WhiteTimer);
                DrawFormatString(0, 17 * 12, GetColor(0, 0, 0), "SpecialAction %d �ł�", SpecialAction);



                DrawFormatString(0, 18 * 12, GetColor(0, 0, 0), "damageFlag %d �ł�", player.damageFlag);
                DrawFormatString(0, 19 * 12, GetColor(0, 0, 0), "damageTimer %d �ł�", player.damageTimer);

                */
                //�A�j���p�̕ϐ����Z
                player.animeTime++;

                //��]�E���]
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

                //�_���[�W
                if (player.damageFlag) {
                    player.damageTimer++;
                    //if (player.damageTimer > MAX_DAMAGE_TIME) {�J��Ԃ��̂ŕs�K�v
                    //    player.damageTimer = MAX_DAMAGE_TIME;
                    //}
                }


                break;

            }

            case 7://�N���A������

                clearText[0]= LoadGraph("�摜/clearText.png");
                clearText[1]= LoadGraph("�摜/clearText_0.png");//����
                clearText[2]= LoadGraph("�摜/clearText_1.png");//����
                clearText[3]= LoadGraph("�摜/clearText_2.png");//�������
                clearText[4]= LoadGraph("�摜/clearText_3.png");//�߂�

                clearIcon[0]= LoadGraph("�摜/clearIcon_0.png");
                clearIcon[1]= LoadGraph("�摜/clearIcon_1.png");
                clearIcon[2]= LoadGraph("�摜/clearIcon_2.png");

                stopBGM();

                scrollCnt = 0;
                ClearStage = false;

                gamemode++;
            case 8://�N���A����
                
                ClearSc();
                break;

            }

            //�u���b�N�A�E�g�z���C�g�A�E�g
               //�u���b�N�z���C�g�`��
            BlackOutRender();
            WhiteOutRender();

            //�u���b�N�z���C�g���Z
            BlackOutTimer();
            WhiteOutTimer();

        }
        // ��ʂ̍X�V
        ScreenFlip();
        NowSc += 3;

    }

    // �I��
    return 0;
}

//HACK: �G����

// �L�����N�^���}�b�v�Ƃ̓����蔻����l�����Ȃ���ړ�����
int CharMove(Player& player,float Size)
{
    float Dummy = 0.0F;
    float hsize;

    // �����̃T�C�Y���Z�o
    hsize = Size * 0.5F;

    //�㉺�`�F�b�N
    {
        //�ő呬�x�`�F�b�N
        if (player.speedY > MAX_SPEED_Y)
            player.speedY = MAX_SPEED_Y;
        if (player.speedY < -MAX_SPEED_Y)
            player.speedY = -MAX_SPEED_Y;

        //���Z
        float oldY = player.y;
        player.y += player.speedY;
        float deltaY = player.y - oldY;//�㉺���ǂ����Ɏg�p

        player.onGround = false;    //�t���O����

        //�����蔻��
        //��
        if (deltaY > 0)
        {
            if (isFloor(player.x, player.y, hsize))//�����̃T�C�Y�͌�X2�{�ɂ��Ă���������??
            {
                //�␳
                player.y -= fmodf(player.y, CHIP_SIZE) + 0.025f;
                player.speedY = player.speedY < 0.0f ? player.speedY : 0.0f;
                player.onGround = true; //�n�ʃt���O
            }

            //���u���b�N
            if (isFloorBlack(player.x, player.y, hsize))//�߂荞�񂾃v���C���[���W
            {
                //�␳
                //Block black = whoBlack(player.x, player.y);
                //���Ƀu���b�N������̂��킩���Ă���̂ŁA���̃}�X�̐^��
                float blackCenterY = ((int)player.y / CHIP_SIZE) * CHIP_SIZE + CHIP_SIZE / 2;
                if(player.y > blackCenterY)//�����Ԃ���Ă���
                {
                    PlaySoundFile("�T�E���h/damege.mp3", DX_PLAYTYPE_BACK);

                    resetStage();
                }
                if (player.y < blackCenterY) {//���ꂪ���u���b�N
                    player.y -= fmodf(player.y, CHIP_SIZE) + 0.025f;
                    player.speedY = player.speedY < 0.0f ? player.speedY : 0.0f;
                    player.onGround = true; //�n�ʃt���O
                }
            }

            //������Ƃ߂肱��ł���̂ł�����Ə�̏��Ŕ�����
            //���u���b�N�ŋ��܂ꂽ�ꍇ����邽��
            if (isFloorBlack(player.x, player.y-1, hsize))
            {
                //�␳
                //Block black = whoBlack(player.x, player.y);
                //���Ƀu���b�N������̂��킩���Ă���̂ŁA���̃}�X�̐^��
                float blackCenterY = ((int)player.y / CHIP_SIZE) * CHIP_SIZE + CHIP_SIZE / 2;
                if (player.y > blackCenterY)//�����Ԃ���Ă���
                {
                    PlaySoundFile("�T�E���h/damege.mp3", DX_PLAYTYPE_BACK);

                    resetStage();
                }
                if (player.y < blackCenterY) {//���ꂪ���u���b�N
                    player.y -= fmodf(player.y, CHIP_SIZE) + 0.025f;
                    player.speedY = player.speedY < 0.0f ? player.speedY : 0.0f;
                    player.onGround = true; //�n�ʃt���O
                }
            }

            if (isFloorNeedle(player.x, player.y, hsize))//�}�b�v�`�b�v�I�ɂ͂Ƃ���
            {
                float needleY = (((int)player.y / CHIP_SIZE)*CHIP_SIZE)+needleOffset;
                if (needleY <= player.y) {
                    //�␳
                    //player.y -= fmodf(player.y, CHIP_SIZE) + 0.025f;
                    //player.y -= fmodf(needleY, CHIP_SIZE) + 0.025f;
                    player.y -= fmodf(needleY, CHIP_SIZE) + 0.025f;
                    player.speedY = player.speedY < 0.0f ? player.speedY : 0.0f;
                    //player.onGround = true; //�n�ʃt���O

                    PlaySoundFile("�T�E���h/damege.mp3", DX_PLAYTYPE_BACK);

                    player.damageFlag = true;
                    resetStage();
                }
            }
        }

        //��
        if (deltaY < 0)
        {
            if (isCeiling(player.x , player.y - Size-playerOffsetY, hsize))//�������T�C�Y�͌�X2�{�ɂ��Ă���������??
            {
                //�␳
                float y = player.y - Size-playerOffsetY;//������2�{
                player.y += CHIP_SIZE - fmodf(y, CHIP_SIZE);
                player.speedY = 0.0f;
            }

            //���u���b�N
            if (isCeilingBlack(player.x, player.y - Size - playerOffsetY, hsize))
            {
                //�␳
                float y = player.y - hsize - playerOffsetY;//������2�{
                //player.y += CHIP_SIZE - fmodf(y, CHIP_SIZE);
                player.speedY = player.speedY > 0.0f ? player.speedY : 0.0f;

                PlaySoundFile("�T�E���h/damege.mp3", DX_PLAYTYPE_BACK);

                resetStage();
            }
            if (isCeilingNeedle(player.x, player.y - Size - playerOffsetY, hsize))//�������T�C�Y�͌�X2�{�ɂ��Ă���������??
            {
                float needleY = (((int)player.y / CHIP_SIZE) * CHIP_SIZE)+CHIP_SIZE - needleOffset;
                if (needleY >= player.y) {
                    //�␳
                    float y = player.y - Size;//������2�{
                    player.y += CHIP_SIZE-needleOffset - fmodf(needleY, CHIP_SIZE);
                    player.speedY = player.speedY > 0.0f ? player.speedY : 0.0f;

                    PlaySoundFile("�T�E���h/damege.mp3", DX_PLAYTYPE_BACK);

                    player.damageFlag = true;
                    resetStage();
                }
            }
        }
    }

    // ���E�`�F�b�N
    {
        //�ő呬�x�`�F�b�N
        if (player.speedX > MAX_SPEED_X)
            player.speedX=MAX_SPEED_X;
        if (player.speedX < -MAX_SPEED_X)
            player.speedX=-MAX_SPEED_X;

        //���Z
        float oldX = player.x;
        player.x += player.speedX;
        float deltaX = player.x - oldX;//���E���ǂ����Ɏg�p


        //�����蔻��
        //�E
        if (deltaX > 0) {
            //��
            if (isWall(player.x + hsize, player.y, Size))//�E���ǂ�
            {
                //�␳
                float hoseiX = player.x + hsize;//TODO:hsize�͂̂��̂������蔻��̉E��
                player.x -= fmodf(hoseiX, CHIP_SIZE ) + 0.025f;//������Ɨ��������̂𑫂�
                player.speedX = 0.0f;
                //�ǃt���O�𗧂Ă��肵�Ă����������H
            }
            if (isWall(player.x + hsize+1, player.y, Size))//������Ə�邱�Ƃ�����̂őj�~
            {
                //�␳
                player.x -= 1 + 0.025f;//������Ɨ��������̂𑫂�
                player.speedX = 0.0f;
                //�ǃt���O�𗧂Ă��肵�Ă����������H
            }
            //���u���b�N
            if (isBlack(player.x  + hsize, player.y))
            {
                //�␳
                float hoseiX = player.x + hsize;//TODO:hsize�͂̂��̂������蔻��̉E��
                player.x -= fmodf(hoseiX, CHIP_SIZE) + 0.025f;//������Ɨ��������̂𑫂�
                player.speedX = 0.0f;
            }
            //�Ƃ��u���b�N
            if (isWallNeedle(player.x + hsize, player.y,Size))
            {
                //�Ƃ��̓����蔻��ɓ��������Ƃ��̂ݕ␳(�㉺�œ������ĂȂ��ĉ��ɓ��͂���ƕ␳�����̂�)
                float needleYDown = ((int)player.y / CHIP_SIZE) * CHIP_SIZE + needleOffset;
                float needleYUp = ((int)player.y / CHIP_SIZE) * CHIP_SIZE*2 - needleOffset;
                if (needleYUp <= player.y&&needleYUp>=player.y-Size|| needleYDown <= player.y&&needleYDown>=player.y-Size) {
                    //�␳
                    float hoseiX = player.x + hsize;//TODO:hsize�͂̂��̂������蔻��̉E��
                    player.x -= fmodf(hoseiX, CHIP_SIZE) + 0.025f;//������Ɨ��������̂𑫂�
                    player.speedX = 0.0f;
                    PlaySoundFile("�T�E���h/damege.mp3", DX_PLAYTYPE_BACK);

                    player.damageFlag = true;
                    resetStage();

                }
            }
            
        }

        //��
        if (deltaX < 0) {
            //��
            if (isWall(player.x - hsize , player.y, Size))//�����ǂ�
            {
                //�␳
                float hoseiX = player.x - hsize;//TODO:hsize�͂̂��̂������蔻��̉E��
                player.x += CHIP_SIZE-fmodf(hoseiX, CHIP_SIZE) + 0.025f;//������Ɨ��������̂𑫂�
                player.speedX = 0.0f;
                //�ǃt���O�𗧂Ă��肵�Ă����������H
            }
            if (isWall(player.x + hsize - 1, player.y, Size))//������Ə�邱�Ƃ�����̂őj�~
            {
                //�␳
                player.x += 1 + 0.025f;//������Ɨ��������̂𑫂�
                player.speedX = 0.0f;
                //�ǃt���O�𗧂Ă��肵�Ă����������H
            }
            //���u���b�N
            if (isBlack(player.x  - hsize , player.y))
            {
                //�␳
                float hoseiX = player.x - hsize;//TODO:hsize�͂̂��̂������蔻��̉E��
                player.x += CHIP_SIZE - fmodf(hoseiX, CHIP_SIZE) + 0.025f;//������Ɨ��������̂𑫂�
                player.speedX = 0.0f;
            }
            //��
            if (isWallNeedle(player.x - hsize, player.y, Size))//�����ǂ�
            {
                //�Ƃ��̓����蔻��ɓ��������Ƃ��̂ݕ␳(�㉺�œ������ĂȂ��ĉ��ɓ��͂���ƕ␳�����̂�)
                float needleYDown = ((int)player.y / CHIP_SIZE) * CHIP_SIZE + needleOffset; 
                float needleYUp = ((int)player.y / CHIP_SIZE) * CHIP_SIZE * 2 - needleOffset;
                if (needleYUp <= player.y && needleYUp >= player.y - Size || needleYDown <= player.y && needleYDown >= player.y - Size) {
                    //�␳
                    float hoseiX = player.x - hsize;//TODO:hsize�͂̂��̂������蔻��̉E��
                    player.x += CHIP_SIZE - fmodf(hoseiX, CHIP_SIZE) + 0.025f;//������Ɨ��������̂𑫂�
                    player.speedX = 0.0f;
                    PlaySoundFile("�T�E���h/damege.mp3", DX_PLAYTYPE_BACK);


                    player.damageFlag = true;
                    resetStage();
                }
                //�ǃt���O�𗧂Ă��肵�Ă����������H
            }
        }
    }

    //���̑��̓����蔻��
    {
        //�S�[���̓����蔻��
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
            PlaySoundFile("�T�E���h/clear.wav", DX_PLAYTYPE_BACK); //���ʉ�
            gamemode = 7;
        }
    }


    
    //���Ԃ̉��Z
    if (!player.onGround && player.speedY < 0) {//�㏸��
        player.jumpTimer++;

        //�ő�l����
        if (player.jumpTimer > MAX_JUMPTIME)
            player.jumpTimer = MAX_JUMPTIME;
    }

    if (!player.onGround && player.speedY >= 0) {//������
        player.fallTimer++; 
        player.jumpTimer = 0;
    }

    //���ԕϐ��̊Ǘ�
    if (player.onGround) {
        player.fallTimer = 0;
        player.jumpTimer = 0;
    }

    // �I��
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

//HACK: �G����
//// �u���b�N���}�b�v�Ƃ̓����蔻����l�����Ȃ���ړ�����
int BlackMove(Block& black,float Size)
{
    float Dummy = 0.0F;
    float hsize;

    // �����̃T�C�Y
    hsize = Size * 0.5F;

    // ���Z
    black.y+= black.speed;
            
    //���`�F�b�N
    {
        //�ő呬�x�`�F�b�N
        if (black.speed > MAX_BLOCK_SPEED_Y)
            black.speed = MAX_BLOCK_SPEED_Y;

        // �^�񒆉��̂����5�h�b�g��
        if (BlackMapHitCheck(black.x, black.y + hsize+5, &Dummy, &black.speed) == 4)
        {
            black.speed = 0;   //�d�͏���
            black.y = ((int)black.y/CHIP_SIZE)*CHIP_SIZE+CHIP_SIZE/2;    //�␳(�ړ���Ŕz��z�u�Ɏ����`)
            black.onGround = true;     //���n�t���O
            int x = black.x / CHIP_SIZE;
            int y = black.y / CHIP_SIZE;
        }
        else if (blackHitBlack(black))
        {
            black.onGround = true;
        }
        else if (BlackMapHitCheck(black.x, black.y + hsize + 5, &Dummy, &black.speed) == 2)//�}�b�v�`�b�v�I�ɂ͂Ƃ���
        {
            black.speed = 0;   //�d�͏���
            black.y = ((int)black.y / CHIP_SIZE) * CHIP_SIZE + CHIP_SIZE / 2;    //�␳(�ړ���Ŕz��z�u�Ɏ����`)
            black.onGround = true;     //���n�t���O
            int x = black.x / CHIP_SIZE;
            int y = black.y / CHIP_SIZE;
            //DrawFormatString(0, 15 * 2, GetColor(0, 0, 0), "black needle itai", StageCnt);
        }
        else
        {
            black.onGround = false;
        }
        
    }
    // �I��
    return 0;
}

//���������m�̓����蔻��
bool blackHitBlack(Block& Black)
{
    for (int i = BlackCount[StageCnt]; i > 0; i--) {//����(�����画�����Ă�)(�������n���Ă��邩����̂�)
        int x0 = (int)Black.x / CHIP_SIZE;
        int x1 = (int)black[i].x / CHIP_SIZE;
        int y0 = (int)Black.y / CHIP_SIZE;
        int y1 = (int)black[i].y / CHIP_SIZE;
        if (Black.No == black[i].No)continue;//�����Ȃ�
        if (x0 != x1)continue;//������������Ȃ�
        if (Black.y > black[i].y)continue;//��������
        if (!black[i].onGround)continue;//���肪���n���Ă���

            if (black[i].y - Black.y <= CHIP_SIZE) {//�Ԃ��`�b�v�T�C�Y�ȉ���
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


//HACK::�G����
int BlackMapHitCheck(float X, float Y,
    float* MoveX, float* MoveY)
{
    // �ړ��ʂ𑫂�
    float afX = X + *MoveX;
    float afY = Y + *MoveY;

    // �����蔻��̂���u���b�N�ɓ������Ă��邩�`�F�b�N   (�ړ���ɕ��ʃu���b�N�����邩)
    if (GetChipParam(afX, afY) == 0)return 4;//���ʃu���b�N
    if (GetChipParam(afX, afY) == 2)return 2;//�Ƃ�
    
    return 0;
}

// �}�b�v�`�b�v�̒l���擾����֐�
int GetChipParam(float X, float Y)
{
    int x, y;

    // �����l�֕ϊ�
    x = (int)X / CHIP_SIZE;
    y = (int)Y / CHIP_SIZE;

    // �}�b�v����͂ݏo�Ă����� 0 ��Ԃ�
    if (x >= MAP_WIDTH || y >= MAP_HEIGHT || x < 0 || y < 0) return 0;

    // �w��̍��W�ɊY������}�b�v�̏���Ԃ�
    return MapData[y][x];
}