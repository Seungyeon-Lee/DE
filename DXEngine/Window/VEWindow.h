#pragma once
class VEWindow
{
public:
	virtual ~VEWindow() noexcept = default;

	static VEWindow* CreatePlatformWindow();

	virtual void Create() = 0;
	virtual void Destroy() = 0;

	virtual void Show() = 0;
	virtual void Hide() = 0;

	virtual void* Handle() const = 0;

	virtual size_t Width() const = 0;
	virtual size_t Height() const = 0;
	virtual float AspectRatio() const = 0;

protected:
	VEWindow() = default;
};

