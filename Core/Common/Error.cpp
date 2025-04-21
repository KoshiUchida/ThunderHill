/**
 * @file   Error.h
 *
 * @brief  �G���[�\���֐��Q�̃w�b�_�t�@�C��
 *
 * @author CatCode
 *
 * @date   11/03
 */

#include "Error.h"

#include <iostream>
#include <DxLib.h>

/// <summary>
/// �G���[���b�Z�[�W��\������
/// </summary>
/// <param name="errorMessage">�G���[���e</param>
void printError(const std::string& errorMessage)
{
	// �Z���ɃG���[���b�Z�[�W���o��
	std::cerr << errorMessage << std::endl;

	// �}�E�X����\���̍ۂɕ\���ɐ؂�ւ���
	if (!GetMouseDispFlag())
		SetMouseDispFlag(TRUE);

	// �G���[���b�Z�[�W�𐶐�
	MessageBox(NULL, errorMessage.c_str(), "�G���[", MB_OK | MB_ICONERROR);
}
