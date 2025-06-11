
#ifndef ILRD_RD1645_FILEMANAGER_HPP
#define ILRD_RD1645_FILEMANAGER_HPP

#include <fstream>

#include "IFileManager.hpp"

namespace ilrd
{

class FileManager final : public IFileManager
{
public:
	explicit FileManager(const std::string& filePath = "./a.dat");
    bool Read(size_t offset, size_t len, std::shared_ptr<char[]> to) override;
	bool Write(size_t offset, size_t len, std::shared_ptr<char[]> from) override;
	~FileManager() override = default;
private:
	std::fstream m_file;
	std::mutex m_mutex;
}; // class FileManager

} // namespace ilrd

#endif //ILRD_RD1645_FILEMANAGER_HPP
