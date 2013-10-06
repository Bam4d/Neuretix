/*
 * RenderNeuralNet.h
 *
 *  Created on: 10 Sep 2013
 *      Author: bam4d
 */

#ifndef RENDERNEURALNET_H_
#define RENDERNEURALNET_H_

#define GLUT_WHEEL_UP   3
#define GLUT_WHEEL_DOWN 4

#include <vector>

class GLEngine;
class AxonList;
class Group;
class Axon;
class Mind;

class NeuralNetRenderer {
public:
	NeuralNetRenderer(char* networkID);
	virtual ~NeuralNetRenderer();

	void addMind(Mind* mind);

	void start();

	int currentMouseButton;

	char* networkID;

private:
	GLEngine* glEngine;
	std::vector<Mind*> minds;

	void renderGroup(Group* group);
	void renderAxons(Axon* axon);

	static NeuralNetRenderer* renderInstance;

	static void render();
	static void resize(int width, int height);
	static void mouseDrag(int x,int y);
	static void mouseEvent(int button, int state, int x, int y);
};

#endif /* RENDERNEURALNET_H_ */
