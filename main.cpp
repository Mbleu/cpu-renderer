#include "scene.h"
#include "controller.h"
#include "renderer.h"
#include "window.h"

int main()
{
	Scene scene;
	Controller controller(scene);
	Renderer renderer(scene);
	//Window window(renderer);

	bool quit{ false };

	while (!quit) {
		controller.updateScene();
		renderer.renderScene();
		//window.update();
	}
}