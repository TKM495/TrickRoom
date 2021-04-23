#include "INCPNTStaticDraw2.hlsli"

PSPNTInputShadow main(VSPNTInput input)
{
	PSPNTInputShadow result;
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
	//���C�e�B���O
	result.norm = mul(input.norm, (float3x3)World);
	result.norm = normalize(result.norm);
	//�X�y�L�����[
	float3 H = normalize(normalize(-LightDir.xyz) + normalize(EyePos.xyz - pos.xyz));
	result.specular = Specular * dot(result.norm, H);
	//�e�N�X�`��UV
	result.tex = input.tex;
	//�e�̂��߂̕ϐ�
	float4 LightModelPos = float4(input.position.xyz, 1.0f);
	//���[���h�ϊ�
	LightModelPos = mul(LightModelPos, World);

	float4 LightSpacePos = mul(LightModelPos, LightView);
	LightSpacePos = mul(LightSpacePos, LightProjection);
	result.lightSpacePos = LightSpacePos;

	// Light ray
	result.lightRay = LightPos.xyz - LightModelPos.xyz;
	//View
	result.lightView = EyePos.xyz - LightModelPos.xyz;


	//�e�̂��߂̕ϐ�
	float4 TAModelPos = float4(input.position.xyz, 1.0f);
	//���[���h�ϊ�
	TAModelPos = mul(TAModelPos, World);

	float4 TASpacePos = mul(TAModelPos,TALightViewR);
	TASpacePos = mul(TASpacePos, TALightProjection);
	result.TASpacePosR = TASpacePos;

	TASpacePos = mul(TAModelPos,TALightViewL);
	TASpacePos = mul(TASpacePos, TALightProjection);
	result.TASpacePosL = TASpacePos;
	return result;
}