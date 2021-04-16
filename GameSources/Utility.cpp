#include "stdafx.h"
#include "Project.h"

namespace basecross {
	namespace Utility {
		const Vec2 GetTextureSize(const wstring& key)
		{
			auto resource = App::GetApp()->GetResource<TextureResource>(key);
			ID3D11Resource* id3d11resource;
			resource->GetShaderResourceView()->GetResource(&id3d11resource);
			D3D11_TEXTURE2D_DESC textureDesc;
			auto texture = static_cast<ID3D11Texture2D*>(id3d11resource);
			texture->GetDesc(&textureDesc);

			return Vec2(textureDesc.Width, textureDesc.Height);
		}
		const Vec2 ConvertToUVCoordinate(const Vec2& coordinate, const wstring& textureName) {
			ConvertToUVCoordinate(coordinate, GetTextureSize(textureName));
		}

		const Vec2 ConvertToUVCoordinate(const Vec2& coordinate, const Vec2& textureSize) {
			Vec2 uv;
			uv.x = coordinate.x / textureSize.x;
			uv.y = coordinate.y / textureSize.y;
			return uv;
		}

		void ConvertToUVCoordinates(const vector<Vec2>& coordinates, const wstring& textureName, vector<Vec2>& uv) {
			ConvertToUVCoordinates(coordinates, GetTextureSize(textureName), uv);
		}

		void ConvertToUVCoordinates(const vector<Vec2>& coordinates, const Vec2& textureSize, vector<Vec2>& uv){
			for (auto& coordinate : coordinates) {
				float x = coordinate.x / textureSize.x;
				float y = coordinate.y / textureSize.y;
				uv.push_back(Vec2(x, y));
			}
		}
	}
}