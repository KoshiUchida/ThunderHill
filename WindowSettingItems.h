/**
 * @file   WindowSettingItems.h
 *
 * @brief  �E�B���h�E�̃f�t�H���g�ݒ肪����w�b�_�[�t�@�C��
 *
 * @author CatCode
 *
 * @date   2024/12/28
 */

#pragma once
#include <string>

/// <summary>
/// �E�C���h�E�ݒ�^
/// </summary>
struct WindowSettings {

	/*�E�C���h�E�̃^�C�g��*/
	std::string WindowTitle;
	
	/*�E�C���h�E�̊g��䗦*/
	double WindowSizeExtendRate;

	/*��S��ʂɃZ�b�g���邩*/
	bool FragChangeWindowMode;

	/*��ʂ̐ݒ�*/
	// ��ʃT�C�Y
	struct {
		int width;
		int height;
	} Screen;

	// �F�[�x
	int ColorBitDepth;

	// �P���[�v�ł̏������x�̉���[ms]
	int RunTimeMin;

	/*�T�E���h�̐ݒ�*/
	int Volume;

	/*�����֌W�̐ݒ�*/
	// �f�t�H���g�t�H���g
	std::string Font;
	// �t�H���g�T�C�Y
	int FontSize;

	/*Log.txt�̐����ݒ�*/
	bool FragOutApplicationLogValid;
};

/// <summary>
/// �E�C���h�E�̐ݒ�N���X
/// </summary>
class WSI
{
public:
	/*�E�C���h�E�̃^�C�g��*/
	std::string WindowTitle;

	/*�E�C���h�E�̊g��䗦*/
	double WindowSizeExtendRate;

	/*��S��ʂɃZ�b�g���邩*/
	bool FragChangeWindowMode;
	/*�X�N���[���̐ݒ�*/
	// ��ʃT�C�Y
	int ScreenWidth;
	int ScreenHeight;
	// ��ʂ̒ǉ����l
	int ScreenLeft;
	int ScreenCenterX;
	int ScreenRight;
	int ScreenTop;
	int ScreenCenterY;
	int ScreenBotton;
	// �F�[�x
	int ColorBitDepth;
	// �P���[�v�ł̏������x�̉���[ms]
	int RunTimeMin;

	/*�T�E���h�̐ݒ�*/
	static constexpr int MaxVolume{ 255 };
	static constexpr int MinVolume{ 0 };
	int Volume;

	/*�����֌W�̐ݒ�*/
	// �f�t�H���g�t�H���g
	std::string Font;
	// �t�H���g�T�C�Y
	int FontSize;
	/*Log.txt�̐����ݒ�*/
	bool FragOutApplicationLogValid;

	/*���C���V�X�e��*/
	WSI(const std::string& filename);
	~WSI() = default;
};