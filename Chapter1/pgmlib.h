/* �K���摜(pgm�`��)�p���C�u���� pgmlib.h */
#include<stdlib.h>
#include<string.h>

/* �萔�錾 */
#define MAX_IMAGESIZE       1280 /* �z�肷��c�E���̍ő��f�� */
#define MAX_BRIGHTNESS       255 /* �z�肷��ő�K���l */
#define GRAYLEVEL            256 /* �z�肷��K����(=�ő�K���l+1) */
#define MAX_FILENAME         256 /* �z�肷��t�@�C�����̍ő咷 */
#define MAX_BUFFERSIZE       256 /* ���p����o�b�t�@�ő咷 */
#define MAX_NUM_OF_IMAGES      5 /* ���p����摜�̖��� */

/* ���ϐ��̐錾 */
/* �摜�f�[�^ image[n][x][y] */
unsigned char image[MAX_NUM_OF_IMAGES][MAX_IMAGESIZE][MAX_IMAGESIZE];
/* image[n] �̉����E�c�� */
int width[MAX_NUM_OF_IMAGES], height[MAX_NUM_OF_IMAGES];

/* �֐��̃v���g�^�C�v�錾 */
/* �K���摜����͂���֐� */
void load_image( int n, char name[] );
  /* n:�摜�ԍ��Cname[]:�t�@�C�����i""�̂Ƃ��̓L�[�{�[�h���́j*/
/* �K���摜���o�͂���֐�*/
void save_image( int n, char name[] );
  /* n:�摜�ԍ��Cname[]:�t�@�C�����i""�̂Ƃ��̓L�[�{�[�h���́j*/
/* �K���摜���R�s�[����֐�*/
void copy_image( int n1, int n2 );
  /* �摜No.n1 �� �摜No.n2�ɃR�s�[���� */
/* �K���摜������������֐�*/
void init_image( int n, unsigned char value );
  /* �摜No.n�̑S��f�̊K���l�������I��value(0�`255)�ɂ��� */

/* �K���摜����͂���֐� */
void load_image( int n, char name[] )
/* n:�摜�ԍ��Cname[]:�t�@�C�����i""�̂Ƃ��̓L�[�{�[�h���́j*/
/* �����C�c���͂��ꂼ�� width[n], height[n] �ɑ������ */
{
    char file_name[MAX_FILENAME]; /* �t�@�C�����p�̕����z�� */
    char buffer[MAX_BUFFERSIZE];  /* �f�[�^�ǂݍ��ݗp��ƕϐ� */
    FILE *fp; /* �t�@�C���|�C���^ */
    int max_gray; /* �ő�K���l */
    int x, y; /* ���[�v�ϐ� */

    /* ���̓t�@�C���̃I�[�v�� */
    if ( name[0] == '\0' ){
        printf("���̓t�@�C���� (*.pgm) : ");
        scanf("%s",file_name);
    } else strcpy( file_name, name );
    if ( (fp = fopen( file_name, "rb" ))==NULL ){
        printf("���̖��O�̃t�@�C���͑��݂��܂���D\n");
        exit(1);
    }
    /* �t�@�C���^�C�v(=P5)�̊m�F */
    fgets( buffer, MAX_BUFFERSIZE, fp );
    if ( buffer[0] != 'P' || buffer[1] != '5' ){
        printf("�t�@�C���̃t�H�[�}�b�g�� P5 �Ƃ͈قȂ�܂��D\n");
        exit(1);
    }
    /* width[n], height[n] �̑���i#����n�܂�R�����g�͓ǂݔ�΂��j */
    width[n] = 0;    height[n] = 0;
    while ( width[n] == 0 || height[n] == 0 ){
        fgets( buffer, MAX_BUFFERSIZE, fp );
        if ( buffer[0] != '#' )
            sscanf( buffer, "%d %d", &width[n], &height[n] );
    }
    /* max_gray �̑���i#����n�܂�R�����g�͓ǂݔ�΂��j */
    max_gray = 0;
    while ( max_gray == 0 ){
        fgets( buffer, MAX_BUFFERSIZE, fp );
        if ( buffer[0] != '#' )
            sscanf( buffer, "%d", &max_gray );
    }
    /* �p�����[�^�̉�ʂւ̕\�� */
    printf("���̉�f�� = %d, �c�̉�f�� = %d\n", width[n], height[n] );
    printf("�ő�K���l = %d\n",max_gray);
    if ( width[n] > MAX_IMAGESIZE || height[n] > MAX_IMAGESIZE ){
        printf("�z��l %d x %d �𒴂��Ă��܂��D\n", 
            MAX_IMAGESIZE, MAX_IMAGESIZE);
        printf("�������������ȉ摜���g���ĉ������D\n");
        exit(1);
    }
    if ( max_gray != MAX_BRIGHTNESS ){
        printf("�ő�K���l���s�K�؂ł��D\n");  exit(1);
    }
    /* �摜�f�[�^��ǂݍ���ŉ摜�p�z��ɑ������ */
    for(y=0;y<height[n];y++)
        for(x=0;x<width[n];x++)
            image[n][x][y] = (unsigned char)fgetc( fp );
    fclose(fp);
    printf("�摜�͐���ɓǂݍ��܂�܂����D\n");
}

/* �K���摜���o�͂���֐�*/
void save_image( int n, char name[] )
/* n:�摜�ԍ��Cname[]:�t�@�C�����i""�̂Ƃ��̓L�[�{�[�h���́j*/
/* �摜�̉����C�c���͂��ꂼ�� width[n], height[n] �ɑ������Ă�����̂Ƃ��� */
{
    char file_name[MAX_FILENAME]; /* �t�@�C�����p�̕����z�� */
    FILE *fp; /* �t�@�C���|�C���^ */
    int x, y; /* ���[�v�ϐ� */

    /* �o�̓t�@�C���̃I�[�v�� */
    if ( name[0] == '\0' ){
        printf("�o�̓t�@�C���� (*.pgm) : ");
        scanf("%s",file_name);
    } else strcpy( file_name, name );
    if ( (fp = fopen(file_name, "wb"))==NULL ){
        printf("�t�@�C�����I�[�v���ł��܂���D\n");
        exit(1);
    }
    /* �t�@�C�����ʎq "P5" ��擪�ɏo�͂��� */
    fputs( "P5\n", fp );
    /* # �Ŏn�܂�R�����g�s�i�ȗ��\�j */
    fputs( "# Created by Image Processing\n", fp );
    /* �摜�̉����C�c���̏o�� */
    fprintf( fp, "%d %d\n", width[n], height[n] );
    /* �ő�K���l�̏o�� */
    fprintf( fp, "%d\n", MAX_BRIGHTNESS );
    /* �摜�f�[�^�̏o�� */
    for(y=0;y<height[n];y++)
        for(x=0;x<width[n];x++)
            fputc( image[n][x][y], fp );
    fclose(fp);
    printf("�摜�͐���ɏo�͂���܂����D\n");
}

/* �K���摜���R�s�[����֐�*/
void copy_image( int n1, int n2 )
/* �摜No.n1���摜No.n2�ɃR�s�[���� */
{
    int x, y; /* ���[�v�ϐ� */

    /* �����C�c���̑�� */
    width[n2] = width[n1];    height[n2] = height[n1];
    /* �K���f�[�^�̃R�s�[ */
    for(y=0;y<height[n1];y++)
        for(x=0;x<width[n1];x++)
            image[n2][x][y] = image[n1][x][y];
}

/* �K���摜������������֐�*/
void init_image( int n, unsigned char value )
/* �摜No.n�̑S��f�̊K���l�������I��value(0�`255)�ɂ��� */
{
    int x, y; /* ���[�v�ϐ� */

    for(y=0;y<height[n];y++)
        for(x=0;x<width[n];x++)
            image[n][x][y] = value;
}
