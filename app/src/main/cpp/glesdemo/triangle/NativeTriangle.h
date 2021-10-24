#pragma once
#include "../../utils/GLUtils.h"

namespace NAMESPACE_NativeTriangle{
	class NativeTriangle {

	public:
		NativeTriangle();

		~NativeTriangle();

		void create();

		void change(int width, int height);

		void draw();

	private:
		GLuint mProgram;
		int mWidth;
		int mHeight;
	};
}

