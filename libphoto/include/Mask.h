#ifndef MASK_H
#define MASK_H

/**
 * Represents a mask that is used when calculating how much influence a color should have on an existing pixel on the canvas.
 */
class Mask {
public:
	Mask(int width, int height, float baseInfluence);
	Mask(int width, int height);
	virtual ~Mask();
	/**
 	 * Returns the influence at the given position
 	 */
	float getInfluence(int x, int y);
	/**
 	 * Populates this mask with all of its influence values.
 	 */
	virtual void populate();
	const int getWidth();
	const int getHeight();

protected:
	static const float DEFAULT_INFLUENCE = 1.0;
	static const float NO_BASE_INFLUENCE = -1.0;
	const int m_width;
	const int m_height;
	float* m_influence;
	const float m_baseInfluence;
	virtual float calculateInfluence(int x, int y) = 0;
};

#endif

