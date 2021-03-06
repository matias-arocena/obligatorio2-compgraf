#pragma once
#include <vector>

#include <pugixml.hpp>
#include <glm/glm.hpp>

#include "Camera.h"
#include "Constants.h"
#include "Color.h"
#include "Light.h"
#include "PositionLight.h"
#include "SceneObject.h"

class Ray;

struct SDL_Renderer;

class Scene
{
public:
	Scene();
	void loadSceneFromFile();
	std::vector<double> getXmlVector(pugi::xml_attribute attr);
	void render(SDL_Renderer* renderer, SDL_Renderer* reflectionRenderer, SDL_Renderer* transimssionRenderer, SDL_Renderer* ambientRenderer, SDL_Renderer* diffuseRenderer, SDL_Renderer* specularRenderer);
private:
	int maxDepth;
	glm::vec3 projectionCenter;
	std::vector<SceneObject*> objects;
	std::vector<PositionLight*> lights;
	Camera *camera;
	Light *ambientLight;
	Color backgroudColor;

	Color rayTrace(const Ray& ray, int depth);
	Color shadow(const CollisionPoint *hit, const Ray& ray, int depth);
	
	double fresnel(const glm::dvec3& direction, const glm::dvec3& normal, const double& inTransmissionCoefficient, const double& outTransmissionCoefficient);
	CollisionPoint* getClosestObject(const Ray& ray, std::vector<CollisionPoint*> collisions);
	Ray getReflectiveRay(const Ray& ray, const CollisionPoint& hit);
	glm::vec3 getReflectiveVector(const glm::vec3 vec, const glm::vec3 axis);
	Ray getTransmissionRay(const Ray& ray, const CollisionPoint& hit);
};

