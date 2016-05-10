//
//  ColorData.h
//  Originally created by the CSci-3081W TAs.
//

#ifndef COLORDATA_H
#define COLORDATA_H

 ///This color data class stores color in floating point format. The Red, Green, Blue, and Alpha channels range from 0.0 to 1.0.
class ColorData
{
public:
	///default colordata with color black (r=0,g=0,b=0)
	ColorData();
	///initialize the colordata with the input rgb values
	ColorData(float r, float g, float b );
	///initialzie the colordata with the input rbg values as well as the alpha value
	ColorData(float r, float g, float b, float a);

	///set the red value
	void setRed(float r);
	///set the blue value
	void setBlue(float b);
	///set the green value
	void setGreen(float g);
	///set the alpha value
	void setAlpha(float a);

	///return the red value
	float getRed() const;
	///return the blue value
	float getBlue() const;
	///return the green value
	float getGreen() const;
	///return the alpha value
	float getAlpha() const;

	/// Returns the "brightness" of the color according to a perceptual metric that
	/// weights the red, green, and blue components of the color non-uniformly.
	float getLuminance() const;

	/// Return a clamped version of this ColorData make sure it doesnt overflow bounds
	ColorData clampedColor() const;

	/// Arithmatic operators (friends so that non-member functions can access private variables)
	friend ColorData operator* (const ColorData& a, float f);
	/// Arithmatic operators (friends so that non-member functions can access private variables)
	friend ColorData operator+ (const ColorData& a, const ColorData& b);
	/// Arithmatic operators (friends so that non-member functions can access private variables)
	friend ColorData operator- (const ColorData& a, const ColorData& b);

private:

	/// General helper function for clamping values between 0 and 1 to avoid overflow
	static inline float clampValue(float input, float a, float b)
	{return input < a ? a : (input > b ? b : input);}
	///store the red value
	float m_red;
	///store the green value
	float m_green;
	///store the blue value
	float m_blue;
	///store the alpha value
	float m_alpha;
};

#endif
