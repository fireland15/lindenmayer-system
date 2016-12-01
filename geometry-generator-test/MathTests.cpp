#define _USE_MATH_DEFINES
#include "stdafx.h"
#include "CppUnitTest.h"

#include <OpenMesh\Core\Mesh\PolyMesh_ArrayKernelT.hh>
#include <OpenMesh\Core\IO\MeshIO.hh>
#include <memory>

#include "../glm/glm.hpp"
#include "../geometry-generator/Math.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace geometrygeneratortest {
	TEST_CLASS(vectorAngleTests) {
	public:
		TEST_METHOD(Radians0) {
			glm::vec3 a(0.0F, 1.0F, 0.0F);
			glm::vec3 b(0.0F, 1.0F, 0.0F);

			float result = fli::geometry_generator::math::vectorAngleRadians(a, b);

			Assert::AreEqual(0.0F, result);
		}

		TEST_METHOD(RadiansPI_2) {
			glm::vec3 a(0.0F, 1.0F, 0.0F);
			glm::vec3 b(1.0F, 0.0F, 0.0F);

			float result = fli::geometry_generator::math::vectorAngleRadians(a, b);

			Assert::AreEqual((float)M_PI_2, result);
		}

		TEST_METHOD(RadiansPI_4) {
			glm::vec3 a(0.0F, 1.0F, 0.0F);
			glm::vec3 b(1.0F, 1.0F, 0.0F);

			float result = fli::geometry_generator::math::vectorAngleRadians(a, glm::normalize(b));

			Assert::AreEqual((float)M_PI_4, result);
		}

		TEST_METHOD(Radians3d) {
			glm::vec3 a(1.0F, 1.0F, 0.0F);
			glm::vec3 b(0.0F, 1.0F, 1.0F);

			float result = fli::geometry_generator::math::vectorAngleRadians(glm::normalize(a), glm::normalize(b));

			Assert::AreEqual((float)M_PI_3, result);
		}

		TEST_METHOD(Degree0) {
			glm::vec3 a(0.0F, 1.0F, 0.0F);
			glm::vec3 b(0.0F, 1.0F, 0.0F);

			float result = fli::geometry_generator::math::vectorAngleDegrees(a, b);

			Assert::AreEqual(0.0F, result);
		}

		TEST_METHOD(Degree90) {
			glm::vec3 a(0.0F, 1.0F, 0.0F);
			glm::vec3 b(1.0F, 0.0F, 0.0F);

			float result = fli::geometry_generator::math::vectorAngleDegrees(a, b);

			Assert::AreEqual(90.0F, result);
		}

		TEST_METHOD(Degree45) {
			glm::vec3 a(0.0F, 1.0F, 0.0F);
			glm::vec3 b(1.0F, 1.0F, 0.0F);

			float result = fli::geometry_generator::math::vectorAngleDegrees(a, glm::normalize(b));

			Assert::AreEqual(45.0F, result);
		}

		TEST_METHOD(Degree60) {
			glm::vec3 a(1.0F, 1.0F, 0.0F);
			glm::vec3 b(0.0F, 1.0F, 1.0F);

			float result = fli::geometry_generator::math::vectorAngleDegrees(glm::normalize(a), glm::normalize(b));

			Assert::IsTrue(abs(result - 60.0F) < FLT_EPSILON);
		}
	};
}