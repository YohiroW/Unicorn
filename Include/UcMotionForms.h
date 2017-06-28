#ifndef _UC_MOTIONFORM_H_
#define _UC_MOTIONFORM_H_
//
#include <cmath>
#include "UcMath.h"
#include "UcMacros.h"

namespace Unicorn
{
	class MotionForm
	{
	public:
		static float linear(float start, float end, float value)
		{
			return (end - start) * value + start;
		}

		static float spring(float start, float end, float value)
		{
			value = Math::clamp(value,0,1);
			value = (sin(value * PI * (0.2f + 2.5f * value * value * value)) * pow(1.0f - value, 2.2f) + value) * (1.0f + (1.2f * (1.0f - value)));
			return start + (end - start) * value;
		}

		static float easeInQuad(float start, float end, float value)
		{
			end -= start;
			return end * value * value + start;
		}

		static float easeOutQuad(float start, float end, float value)
		{
			end -= start;
			return -end * value * (value - 2) + start;
		}

		static float easeInOutQuad(float start, float end, float value)
		{
			value /= .5f;
			end -= start;
			if (value < 1)
				return end / 2 * value * value + start;
			value--;
			return -end / 2 * (value * (value - 2) - 1) + start;
		}

		static float easeInCubic(float start, float end, float value)
		{
			end -= start;
			return end * value * value * value + start;
		}

		static float easeOutCubic(float start, float end, float value)
		{
			value--;
			end -= start;
			return end * (value * value * value + 1) + start;
		}

		static float easeInOutCubic(float start, float end, float value)
		{
			value /= .5f;
			end -= start;
			if (value < 1)
				return end / 2 * value * value * value + start;
			value -= 2;
			return end / 2 * (value * value * value + 2) + start;
		}

		static float easeInQuart(float start, float end, float value)
		{
			end -= start;
			return end * value * value * value * value + start;
		}

		static float easeOutQuart(float start, float end, float value)
		{
			value--;
			end -= start;
			return -end * (value * value * value * value - 1) + start;
		}

		static float easeInOutQuart(float start, float end, float value)
		{
			value /= .5f;
			end -= start;
			if (value < 1)
				return end / 2 * value * value * value * value + start;
			value -= 2;
			return -end / 2 * (value * value * value * value - 2) + start;
		}

		static float easeInQuint(float start, float end, float value)
		{
			end -= start;
			return end * value * value * value * value * value + start;
		}

		static float easeOutQuint(float start, float end, float value)
		{
			value--;
			end -= start;
			return end * (value * value * value * value * value + 1) + start;
		}

		static float easeInOutQuint(float start, float end, float value)
		{
			value /= .5f;
			end -= start;
			if (value < 1)
				return end / 2 * value * value * value * value * value + start;
			value -= 2;
			return end / 2 * (value * value * value * value * value + 2) + start;
		}

		static float easeInSine(float start, float end, float value)
		{
			end -= start;
			return -end * cos(value / 1 * (PI / 2)) + end + start;
		}

		static float easeOutSine(float start, float end, float value)
		{
			end -= start;
			return end * sin(value / 1 * (PI / 2)) + start;
		}

		static float easeInOutSine(float start, float end, float value)
		{
			end -= start;
			return -end / 2 * (cos(PI * value / 1) - 1) + start;
		}

		static float easeInExpo(float start, float end, float value)
		{
			end -= start;
			return end * pow(2, 10 * (value / 1 - 1)) + start;
		}

		static float easeOutExpo(float start, float end, float value)
		{
			end -= start;
			return end * (-pow(2, -10 * value / 1) + 1) + start;
		}

		static float easeInOutExpo(float start, float end, float value)
		{
			value /= .5f;
			end -= start;
			if (value < 1)
				return end / 2 * pow(2, 10 * (value - 1)) + start;
			value--;
			return end / 2 * (-pow(2, -10 * value) + 2) + start;
		}

		static float easeInCirc(float start, float end, float value)
		{
			end -= start;
			return -end * (sqrt(1 - value * value) - 1) + start;
		}

		static float easeOutCirc(float start, float end, float value)
		{
			value--;
			end -= start;
			return end * sqrt(1 - value * value) + start;
		}

		static float easeInOutCirc(float start, float end, float value)
		{
			value /= .5f;
			end -= start;
			if (value < 1)
				return -end / 2 * (sqrt(1 - value * value) - 1) + start;
			value -= 2;
			return end / 2 * (sqrt(1 - value * value) + 1) + start;
		}

		static float easeInBounce(float start, float end, float value)
		{
			end -= start;
			float d = 1.0f;
			return end - easeOutBounce(0, end, d - value) + start;
		}

		static float easeOutBounce(float start, float end, float value)
		{
			value /= 1.0f;
			end -= start;
			if (value < (1 / 2.75f)) {
				return end * (7.5625f * value * value) + start;
			}
			else if (value < (2 / 2.75f)) {
				value -= (1.5f / 2.75f);
				return end * (7.5625f * (value)* value + .75f) + start;
			}
			else if (value < (2.5 / 2.75)) {
				value -= (2.25f / 2.75f);
				return end * (7.5625f * (value)* value + .9375f) + start;
			}
			else {
				value -= (2.625f / 2.75f);
				return end * (7.5625f * (value)* value + .984375f) + start;
			}
		}

		static float easeInOutBounce(float start, float end, float value)
		{
			end -= start;
			float d = 1.0f;
			if (value < d / 2)
				return easeInBounce(0, end, value * 2) * 0.5f + start;
			else
				return easeOutBounce(0, end, value * 2 - d) * 0.5f + end * 0.5f + start;
		}

		static float easeInBack(float start, float end, float value)
		{
			end -= start;
			value /= 1;
			float s = 1.70158f;
			return end * (value)* value * ((s + 1) * value - s) + start;
		}

		static float easeOutBack(float start, float end, float value)
		{
			float s = 1.70158f;
			end -= start;
			value = (value / 1) - 1;
			return end * ((value)* value * ((s + 1) * value + s) + 1) + start;
		}

		static float easeInOutBack(float start, float end, float value)
		{
			float s = 1.70158f;
			end -= start;
			value /= .5f;
			if ((value) < 1) {
				s *= (1.525f);
				return end / 2 * (value * value * (((s)+1) * value - s)) + start;
			}
			value -= 2;
			s *= (1.525f);
			return end / 2 * ((value)* value * (((s)+1) * value + s) + 2) + start;
		}

		static float punch(float amplitude, float value)
		{
			float s = 9;
			if (value == 0) {
				return 0;
			}
			if (value == 1) {
				return 0;
			}
			float period = 1 * 0.3f;
			s = period / (2 * PI) * asin(0);
			return (amplitude * pow(2, -10 * value) * sin((value * 1 - s) * (2 * PI) / period));
		}

		static float easeInElastic(float start, float end, float value)
		{
			end -= start;

			float d = 1.0f;
			float p = d * .3f;
			float s = 0;
			float a = 0;

			if (value == 0)
				return start;

			if ((value /= d) == 1)
				return start + end;

			if (a == 0.0f || a < abs(end)) {
				a = end;
				s = p / 4;
			}
			else {
				s = p / (2 * PI) * asin(end / a);
			}

			return -(a * pow(2, 10 * (value -= 1)) * sin((value * d - s) * (2 * PI) / p)) + start;
		}

		static float easeOutElastic(float start, float end, float value)
		{
			end -= start;

			float d = 1.0f;
			float p = d * .3f;
			float s = 0;
			float a = 0;

			if (value == 0)
				return start;

			if ((value /= d) == 1)
				return start + end;

			if (a == 0.0f || a < abs(end)) {
				a = end;
				s = p / 4;
			}
			else {
				s = p / (2 * PI) * asin(end / a);
			}

			return (a * pow(2, -10 * value) * sin((value * d - s) * (2 * PI) / p) + end + start);
		}

		static float easeInOutElastic(float start, float end, float value)
		{
			end -= start;

			float d = 1.0f;
			float p = d * .3f;
			float s = 0;
			float a = 0;

			if (value == 0)
				return start;

			if ((value /= d / 2) == 2)
				return start + end;

			if (a == 0.0f || a < abs(end)) {
				a = end;
				s = p / 4;
			}
			else {
				s = p / (2 * PI) * asin(end / a);
			}

			if (value < 1)
				return -0.5f * (a * pow(2, 10 * (value -= 1)) * sin((value * d - s) * (2 * PI) / p)) + start;
			return a * pow(2, -10 * (value -= 1)) * sin((value * d - s) * (2 * PI) / p) * 0.5f + end + start;
		}
	};
}



#endif