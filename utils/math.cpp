#include "math.h"

math g_Math;

//not taking credit for any of this math

void math::VectorAngles(const c_vector3d& vecForward, c_vector3d& vecAngles)
{
	c_vector3d vecView;
	if (vecForward[1] == 0.f && vecForward[0] == 0.f)
	{
		vecView[0] = 0.f;
		vecView[1] = 0.f;
	}
	else
	{
		vecView[1] = atan2(vecForward[1], vecForward[0]) * 180.f / 3.14159265358979323846f;

		if (vecView[1] < 0.f)
			vecView[1] += 360.f;

		vecView[2] = sqrt(vecForward[0] * vecForward[0] + vecForward[1] * vecForward[1]);

		vecView[0] = atan2(vecForward[2], vecView[2]) * 180.f / 3.14159265358979323846f;
	}

	vecAngles[0] = -vecView[0];
	vecAngles[1] = vecView[1];
	vecAngles[2] = 0.f;
}

/*void math::VectorAngles(const c_vector3d& forward, c_vector3d& up, c_vector3d& angles) {
//	c_vector3d left = cross(up, forward);
	c_vector3d left = up.cross;
	c_vector3d left = forward.cross;
	left.normalize();

	float forwardDist = forward.length2d();

	if (forwardDist > 0.001f) {
		angles.x = atan2f(-forward.z, forwardDist) * 180 / M_PI;
		angles.y = atan2f(forward.y, forward.x) * 180 / M_PI;

		float upZ = (left.y * forward.x) - (left.x * forward.y);
		angles.z = atan2f(left.z, upZ) * 180 / M_PI;
	}
	else {
		angles.x = atan2f(-forward.z, forwardDist) * 180 / M_PI;
		angles.y = atan2f(-left.x, left.y) * 180 / M_PI;
		angles.z = 0;
	}
}*/

c_vector3d math::CalcAngle(const c_vector3d& vecSource, const c_vector3d& vecDestination) // cssimp
{
	c_vector3d vAngle;
	c_vector3d delta((vecSource.x - vecDestination.x), (vecSource.y - vecDestination.y), (vecSource.z - vecDestination.z));
	double hyp = sqrt(delta.x * delta.x + delta.y * delta.y);

	vAngle.x = float(atanf(float(delta.z / hyp)) * 57.295779513082f);
	vAngle.y = float(atanf(float(delta.y / delta.x)) * 57.295779513082f);
	vAngle.z = 0.0f;

	if (delta.x >= 0.0)
		vAngle.y += 180.0f;

	return vAngle;
}


vec_t math::VectorNormalize(c_vector3d& v)
{
	vec_t l = v.length();

	if (l != 0.0f)
	{
		v /= l;
	}
	else
	{
		v.x = v.y = 0.0f; v.z = 1.0f;
	}

	return l;
}

void math::AngleVectors(const c_vector3d& angles, c_vector3d* forward)
{
	Assert(s_bMathlibInitialized);
	Assert(forward);

	float	sp, sy, cp, cy;

	sy = sin(DEG2RAD(angles[1]));
	cy = cos(DEG2RAD(angles[1]));

	sp = sin(DEG2RAD(angles[0]));
	cp = cos(DEG2RAD(angles[0]));

	forward->x = cp * cy;
	forward->y = cp * sy;
	forward->z = -sp;
}

void math::NormalizeAngles(c_vector3d& angles)
{
	for (auto i = 0; i < 3; i++) {
		while (angles[i] < -180.0f) angles[i] += 360.0f;
		while (angles[i] > 180.0f) angles[i] -= 360.0f;
	}
}

float math::NormalizeYaw(float yaw)
{
	if (yaw > 180)
		yaw -= (round(yaw / 360) * 360.f);
	else if (yaw < -180)
		yaw += (round(yaw / 360) * -360.f);

	return yaw;
}

void sin_cos(float radian, float* sin, float* cos)
{
	*sin = std::sin(radian);
	*cos = std::cos(radian);
}

void math::AngleVectors(const c_vector3d& angles, c_vector3d* forward, c_vector3d* right, c_vector3d* up)
{
	float sp, sy, sr, cp, cy, cr;

	sin_cos(GRD_TO_BOG(angles.x), &sp, &cp);
	sin_cos(GRD_TO_BOG(angles.y), &sy, &cy);
	sin_cos(GRD_TO_BOG(angles.z), &sr, &cr);

	if (forward != nullptr)
	{
		forward->x = cp * cy;
		forward->y = cp * sy;
		forward->z = -sp;
	}

	if (right != nullptr)
	{
		right->x = -1 * sr * sp * cy + -1 * cr * -sy;
		right->y = -1 * sr * sp * sy + -1 * cr * cy;
		right->z = -1 * sr * cp;
	}

	if (up != nullptr)
	{
		up->x = cr * sp * cy + -sr * -sy;
		up->y = cr * sp * sy + -sr * cy;
		up->z = cr * cp;
	}
}

void math::RandomSeed(int seed)
{
	static auto random_seed = reinterpret_cast<void(*)(int)>(GetProcAddress(GetModuleHandleA("vstdlib.dll"), "RandomSeed"));

	random_seed(seed);
}

float math::RandomFloat(float min, float max)
{
	static auto random_float = reinterpret_cast<float(*)(float, float)>(GetProcAddress(GetModuleHandleA("vstdlib.dll"), "RandomFloat"));

	return random_float(min, max);
}

int math::Random(int min, int max)
{
	return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

void math::ClampAngles(c_vector3d& angles) {
	if (angles.y > 180.0f)
		angles.y = 180.0f;
	else if (angles.y < -180.0f)
		angles.y = -180.0f;

	if (angles.x > 89.0f)
		angles.x = 89.0f;
	else if (angles.x < -89.0f)
		angles.x = -89.0f;

	angles.z = 0;
}

bool math::Clamp(c_vector3d& angles)
{
	c_vector3d a = angles;
	NormalizeAngles(a);
	ClampAngles(a);

	if (isnan(a.x) || isinf(a.x) ||
		isnan(a.y) || isinf(a.y) ||
		isnan(a.z) || isinf(a.z)) {
		return false;
	}
	else {
		angles = a;
		return true;
	}
}

float math::GRD_TO_BOG(float GRD) {
	return (M_PI / 180.f) * GRD;
}

c_vector3d math::ProjectPoint(c_vector3d Origin, double Yaw, double Distance)
{
	return (Origin + c_vector3d((Distance * sin(GRD_TO_BOG(Yaw))), -(Distance * cos(GRD_TO_BOG(Yaw))), 0));
}

float math::Distance(c_vector2d point1, c_vector2d point2)
{
	float diffY = point1.y - point2.y;
	float diffX = point1.x - point2.x;
	return sqrt((diffY * diffY) + (diffX * diffX));
}

bool math::InScreen(int x, int y, int screenwidth, int screenheight) {
	if (screenwidth > x&& screenheight > y&& x > 0 && y > 0)
		return true;
	return false;
}