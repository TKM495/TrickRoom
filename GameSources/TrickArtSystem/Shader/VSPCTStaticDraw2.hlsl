#include "INCPNTStaticDraw2.hlsli"

PSPCTInput main(VSPCTInput input)
{
	PSPCTInput result;
	//���_�̈ʒu��ϊ�
	float4 pos = float4(input.position.xyz, 1.0f);
	//���[���h�ϊ�
	pos = mul(pos, World);
	//�r���[�ϊ�
	pos = mul(pos, View);
	//�ˉe�ϊ�
	pos = mul(pos, Projection);
	//�s�N�Z���V�F�[�_�ɓn���ϐ��ɐݒ�
	result.position = pos;
	result.color = input.color;
	//�e�N�X�`��UV
	result.tex = input.tex;

	//�e�̂��߂̕ϐ�
	float4 TAModelPos = float4(input.position.xyz, 1.0f);
	//���[���h�ϊ�
	TAModelPos = mul(TAModelPos, World);

	float4 TASpacePos = mul(TAModelPos, TALightViewR);
	TASpacePos = mul(TASpacePos, TALightProjection);
	result.TASpacePosR = TASpacePos;

	TASpacePos = mul(TAModelPos, TALightViewL);
	TASpacePos = mul(TASpacePos, TALightProjection);
	result.TASpacePosL = TASpacePos;
	return result;
}