#pragma once

namespace GAPI_FORMAT
{
	enum K
	{
		FORMAT_UNKNOWN = 0,
		FORMAT_D24_UNORM_S8_UINT 
	};
};

namespace GAPI_BIND_FLAGS
{
    enum K
    {
        BIND_VERTEX_BUFFER = 1,
        BIND_INDEX_BUFFER ,
        BIND_CONSTANT_BUFFER ,
        SHADER_RESOURCE ,
        RENDER_TARGET ,
        DEPTH_STENCIL ,
    };
};