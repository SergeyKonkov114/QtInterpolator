#pragma once

#include <vector>

enum class InterpolationType {
	LINEAR,
	SQUARE,
	SPLINE
};

class Interpolator {
public:
	Interpolator(const std::vector<double>& data, int gridSize);
	std::vector<double> interpolate(InterpolationType type) const;
private:
	std::vector<double> linearInterpolation() const;
	std::vector<double> squareInterpolation() const;
	std::vector<double> splineInterpolation() const;
private:
	std::vector<double> data_;
	int gridSize_;
};
