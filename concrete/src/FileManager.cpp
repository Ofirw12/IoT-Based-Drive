
#include <mutex>

#include "FileManager.hpp"


ilrd::FileManager::FileManager(const std::string& filePath)
	: m_file(filePath)
{}

bool ilrd::FileManager::Read(size_t offset, size_t len, std::shared_ptr<char[]> to)
{
	std::unique_lock lock(m_mutex);
	m_file.seekg(offset);
	m_file.read(to.get(), len);
	return m_file.good();
}

bool ilrd::FileManager::Write(size_t offset, size_t len, std::shared_ptr<char[]> from)
{
	std::unique_lock lock(m_mutex);
	m_file.seekp(offset);
	m_file.write(from.get(), len);
	m_file.flush();
	return m_file.good();
}
