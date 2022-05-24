#pragma once

namespace rpg::util {
class NoMoveNoCopy {
public:
	NoMoveNoCopy() = default;
	~NoMoveNoCopy() = default;
	NoMoveNoCopy(const NoMoveNoCopy&) = delete;
	void operator=(const NoMoveNoCopy&) = delete;
	NoMoveNoCopy(NoMoveNoCopy&&) = delete;
	void operator=(NoMoveNoCopy&&) = delete;
};
} // namespace rpg::util
