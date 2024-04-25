#include "base.h"

#ifndef M_PI
#define M_PI 3.141592653589793
#endif

typedef enum typetag_e {
    CYLINDER,
    CUBOID,
    SPHERE,
} TypeTag;

typedef struct cylinder_s {
    double r, h;
} Cylinder;

typedef struct cuboid_s {
    double a, b, c;
} Cuboid;

typedef struct sphere_s {
    double r;
} Sphere;

typedef struct body_s {
    // todo
	 TypeTag tag;
	union{
		 Cylinder cylinder;
		 Cuboid cuboid;
		 Sphere sphere;
	};
} Body;

Body make_cylinder(double r, double h) {
    // todo
	require("non-negative radius", r > 0);
	require("non-negative height", h > 0);
	Body s;
	s.tag = CYLINDER;
	s.cylinder.r = r;
	s.cylinder.h = h;
	return s;
}

Body make_cuboid(double a, double b, double c) {
    // todo
	require("non-negative", a > 0 && b > 0 && c > 0);
	Body s;
	s.tag = CUBOID;
	s.cuboid.a = a;
	s.cuboid.b = b;
	s.cuboid.c = c;
	return s;

}

Body make_sphere(double r) {
    // todo
	require("non-negative", r > 0);
	Body s;
	s.tag = SPHERE;
	s.sphere.r = r;
	return s;

}

double volume(Body body) {
    // todo
	switch(body.tag){
		case SPHERE:
			return 4/3.0 * M_PI * pow(body.sphere.r, 3);
			break;
		case CUBOID:
			return body.cuboid.a * body.cuboid.b * body.cuboid.c;
			break;
		case CYLINDER:
			return pow(body.cylinder.r, 2) * M_PI * body.cylinder.h;
			break;
	}
	return -1;
}

void volume_test(void) {
    test_within_d(volume(make_sphere(2)), 4 /3.0 * M_PI * 2 * 2 * 2, 1e-6);
    test_within_d(volume(make_cuboid(2, 3, 4)), 2 * 3 * 4, 1e-6);
    test_within_d(volume(make_cylinder(3, 4)), 4 * M_PI * 3 * 3 , 1e-6);
}

int main(void) {
    volume_test();
    return 0;
}
