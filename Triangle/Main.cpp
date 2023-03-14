#include "Launch.h"
#include "Triangle.h"

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPWSTR, _In_ int nCmdShow)
{
	Triangle triangle;
	return Entry::RunApplication(triangle, TEXT("Triangle"), hInstance, nCmdShow);
}
