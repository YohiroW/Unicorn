

inline int Game::getRunningState() const{
	return _runningState;
}
//
inline double Game::getTime() const{
	return glfwGetTime();
}
//
inline float Game::getWidthHeightRatio() const{
	return (float)_currentWnd->getWindowWidth() / (float)_currentWnd->getWindowHeight();
}

inline int Game::getWidth() const{
	return _currentWnd->getWindowWidth();
}

inline int Game::getHeight() const{
	return _currentWnd->getWindowHeight();
}