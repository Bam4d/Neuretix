/*
 * RenderNeuralNet.cpp
 *
 *  Created on: 10 Sep 2013
 *      Author: bam4d
 */

#include "../inc/NeuralNetRenderer.h"

#include "../../../Neuretix/src/inc/Axon.h"
#include "../../../Neuretix/src/inc/Neuron.h"
#include "../../../Neuretix/src/inc/Group.h"
#include "../../../Neuretix/src/inc/Mind.h"
#include "../inc/GLEngine.h"

NeuralNetRenderer* NeuralNetRenderer::renderInstance = NULL;

NeuralNetRenderer::NeuralNetRenderer(char* networkID) {

	this->glEngine = new GLEngine();

	this->networkID = networkID;

	renderInstance = this;

}

NeuralNetRenderer::~NeuralNetRenderer() {

	delete glEngine;
}

void NeuralNetRenderer::addMind(Mind* mind) {
	minds.push_back(mind);
}

void NeuralNetRenderer::start() {

	glEngine->CreateGLWindow(networkID,1280,1024);

	glutDisplayFunc(NeuralNetRenderer::render);
	glutReshapeFunc(NeuralNetRenderer::resize);

	glutMotionFunc(NeuralNetRenderer::mouseDrag);
	glutMouseFunc(NeuralNetRenderer::mouseEvent);
	glutIdleFunc(NeuralNetRenderer::render);
	glutMainLoop();
}

void NeuralNetRenderer::mouseEvent(int button, int state, int x, int y) {
	if(state == GLUT_DOWN)
			renderInstance->currentMouseButton = button;
	    else
	    	renderInstance->currentMouseButton = 0;

	    switch(button)
	    {
	        case GLUT_LEFT_BUTTON:
	            renderInstance->glEngine->nmx = x;
	            renderInstance->glEngine->nmy = y;
	            break;
	        case GLUT_MIDDLE_BUTTON:

	            break;
	        case GLUT_RIGHT_BUTTON:
	            renderInstance->glEngine->nmx = x;
	            renderInstance->glEngine->nmy = y;
	            break;
	        case GLUT_WHEEL_UP:
	            renderInstance->glEngine->zDelta+=30;
	            renderInstance->glEngine->windowposz = GLEngine::CalcZoom(renderInstance->glEngine->zDelta);
	            break;
	        case GLUT_WHEEL_DOWN:
	            renderInstance->glEngine->zDelta-=30;
	            renderInstance->glEngine->windowposz = GLEngine::CalcZoom(renderInstance->glEngine->zDelta);
	            break;
	    }

	    return;
}

void NeuralNetRenderer::mouseDrag(int x, int y) {

	    switch(renderInstance->currentMouseButton)
	    {
	        case GLUT_LEFT_BUTTON:
	        	renderInstance->glEngine->pmx = renderInstance->glEngine->nmx;
	            renderInstance->glEngine->pmy = renderInstance->glEngine->nmy;
	            renderInstance->glEngine->nmx = x;
	            renderInstance->glEngine->nmy = y;
	            renderInstance->glEngine->windowposx += GLEngine::CalcPan(-renderInstance->glEngine->pmx,-renderInstance->glEngine->nmx);
	            renderInstance->glEngine->windowposy += GLEngine::CalcPan(renderInstance->glEngine->pmy,renderInstance->glEngine->nmy);
	            break;
	        case GLUT_MIDDLE_BUTTON:

	            break;
	        case GLUT_RIGHT_BUTTON:
	            renderInstance->glEngine->pmx = renderInstance->glEngine->nmx;
	            renderInstance->glEngine->pmy = renderInstance->glEngine->nmy;
	            renderInstance->glEngine->nmx = x;
	            renderInstance->glEngine->nmy = y;
	            renderInstance->glEngine->windowrotx += GLEngine::CalcRot(renderInstance->glEngine->pmx,renderInstance->glEngine->nmx);
	            renderInstance->glEngine->windowroty += GLEngine::CalcRot(renderInstance->glEngine->pmy,renderInstance->glEngine->nmy);
	            break;


	}
}

void NeuralNetRenderer::resize(int width,int height) {
	renderInstance->glEngine->ReSizeGLScene(width,height);
}

// This includes support for multiple render contexts, need to have a map of NeuralNetRenderer objects and add to it and iterate through, setting context each time
void NeuralNetRenderer::render() {

	renderInstance->glEngine->beginRender();

	for (int m_c = 0; m_c < renderInstance->minds.size(); m_c++) {
		Mind * neuralNetwork = renderInstance->minds[m_c];
		if (neuralNetwork->RenderGraphics) {
			Axon * axons = neuralNetwork->axons.Head; //make rendering as efficient as possible

			// Render the groups of neurons
			for (int l_c = 0; l_c < neuralNetwork->cluster.size(); l_c++) {
				renderInstance->renderGroup(neuralNetwork->cluster[l_c]);
			}

			// Render the axons


			//renderInstance->renderAxons(axons);

		}
	}

	renderInstance->glEngine->swapBuffer();
}

void NeuralNetRenderer::renderGroup(Group* group) {

	for (int n_c = 0; n_c < group->neurons.size(); n_c++) {
		if (group->neurons[n_c]->refractory_countdown > 0) {
			glEngine->drawCube(
					group->neurons[n_c]->position.x,
					group->neurons[n_c]->position.y,
					group->neurons[n_c]->position.z, 0.1f,
					1.0f, 1.0f, 1.0f);

			//if the neuron is in TW mode, can use the refactory countdown here to animate
			if (group->neurons[n_c]->ParentMind->_t_Window != NULL)
				group->neurons[n_c]->refractory_countdown = 0;
		}

		else {
			glEngine->drawCube(
					group->neurons[n_c]->position.x,
					group->neurons[n_c]->position.y,
					group->neurons[n_c]->position.z, 0.1f,
					group->neurons[n_c]->neuCol.r,
					group->neurons[n_c]->neuCol.g,
					group->neurons[n_c]->neuCol.b);
		}
	}
}


void NeuralNetRenderer::renderAxons(Axon * axon) {
	if (axon != NULL) {

		do {

			if (axon->destination != NULL) //destination will be null if fire goes to external function
					{
				PlotPoint nsourcepos = axon->source->position;
				PlotPoint ndestpos = axon->destination->position;
				if (axon->source->ParentGroupID == axon->destination->ParentGroupID
						&& axon->destination->id <= axon->source->id) {
					//plot curves
					if (axon->source->refractory_countdown > 0) {
						if (axon->fire_magnitude > 0)
							glEngine->drawCurve(&axon->ctrlpoints[0][0], 3, 4, 0, 1.0, 0);
						else
							glEngine->drawCurve(&axon->ctrlpoints[0][0], 3, 4, 1.0f, 0, 0);

					} else {
						glEngine->drawCurve(&axon->ctrlpoints[0][0], 3, 4, 0.3f, 0.3f, 1.0f);
					}
				} else if (axon->source->refractory_countdown > 0) {

					if (axon->fire_magnitude > 0)
						glEngine->drawLine(nsourcepos.x, nsourcepos.y,
								nsourcepos.z, ndestpos.x, ndestpos.y,
								ndestpos.z, 0, 1.0f, 0);
					else
						glEngine->drawLine(nsourcepos.x, nsourcepos.y,
								nsourcepos.z, ndestpos.x, ndestpos.y,
								ndestpos.z, 1.0f, 0, 0);

				} else {
					glEngine->drawLine(nsourcepos.x, nsourcepos.y, nsourcepos.z,
							ndestpos.x, ndestpos.y, ndestpos.z, 0.3f, 0.3f,
							1.0f);
				}
			}
			axon = axon->next;
		} while (axon != NULL);
	}
}

