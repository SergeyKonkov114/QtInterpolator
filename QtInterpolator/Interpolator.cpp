#include "Interpolator.h"
#include <iostream>

Interpolator::Interpolator(const std::vector<double>& data, int gridSize)
	: data_(data)
	, gridSize_(gridSize)
{
}

std::vector<double> Interpolator::linearInterpolation() const {
	const std::vector<double>& y = data_;
	int n = gridSize_;
	if (n <= 0) {
		throw std::invalid_argument("Grid size must be greater than zero");
	}
	if (y.size() == 0) {
		throw std::invalid_argument("Array Y is empty.");
	};
	std::vector<double> y_proc;
	for (int i = 0; i < static_cast<int>(y.size() - 1u); ++i) {
		for (int j = 0; j < n; ++j) {
			y_proc.push_back((y[i] * (n - j) + y[i + 1] * j) / n);
		}
	}
	y_proc.push_back(y.back());
	return y_proc;
}

std::vector<double> Interpolator::squareInterpolation() const {
	const std::vector<double>& y = data_;
	int n = gridSize_;
	if (n <= 0) {
		throw std::invalid_argument("Grid size must be greater than zero.");
	}
	if (y.size() == 0) {
		throw std::invalid_argument("Array Y is empty.");
	};
	if (y.size() < 3u) {
		return linearInterpolation();
	}
	std::vector<double> y_proc;
	for (int i = 0; i < static_cast<int>(y.size() - 2u); i += 2) {
		int m = 2 * n;
		for (int j = 0; j < m; ++j) {
			double elem = y[i] * ((j - m / 2.) * (j - m)) / (m / 2. * m)
				+ y[i + 1] * (j * (j - m)) / (-m / 2. * m / 2.)
				+ y[i + 2] * (j * (j - m / 2.)) / (m * m / 2.);
			y_proc.push_back(elem);
		}
	}
	y_proc.push_back(y.back());
	return y_proc;
}

std::vector<double> Interpolator::splineInterpolation() const {
	//Not implemented
	return {};
}

std::vector<double> Interpolator::interpolate(InterpolationType type) const {
	switch (type) {
	case InterpolationType::LINEAR:
		return linearInterpolation();
		break;
	case InterpolationType::SQUARE:
		return squareInterpolation();
		break;
	case InterpolationType::SPLINE:
		//Not implemented
		return {};
		break;
	}
}