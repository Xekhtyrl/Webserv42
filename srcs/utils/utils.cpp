#include "../../includes/webserv.hpp"
#include <ctime>

std::string strTrim(std::string str, std::string set) {
	int	n;
	int	start;

	if (str.empty())
		return ("");
	start = 0;
	while (set.find(str[start], 0) <= str.size())
		start++;
	n = str.size() - 1;
	while (set.find(str[n], 0) <= str.size() && n != 0)
		n--;
	return (str.substr(start, n - start + 1));
}

std::string	intToHex(int n) {
	std::stringstream ss;
	ss << std::hex << n;
	std::string res (ss.str());
	return res;
}

std::string	getTimeStamp() {
	time_t timestamp;
	time(&timestamp);

	std::string timeStr(ctime(&timestamp));
	return strTrim(timeStr, "\n");
}

bool	isBinaryFile(std::string filename, std::string& type) {
	std::string image[] = {".png", ".jpg", ".jpeg", ".gif", ".bmp", ".tiff", ".ico", ".svg", ""};
	std::string audio[] = {".mp3", ".wav", ".flac", ".ogg", ".aac", ".wma", ""}; 
	std::string video[] = {".mp4", ".avi", ".mov", ".mkv", ".wmv", ".flv", ""}; 
	std::string	exec[] = {".exe", ".dll", ".so", ".bin", ".elf", ".dylib", ".out", ""};
	std::string	compr[] = {".zip", ".rar", ".tar", ".gz", ".7z", ".bz2", ""};
	std::string	doc[] = {".pdf", ".doc", ".docx", ".xls", ".xlsx", ".ppt", ".pptx", ""};
	std::string	oth[] = {".psd", ".iso", ".dat", ".class", ".swf", ".ttf", ".otf", ""};

	for (int i = 0; !image[i].empty(); i++){
		if (filename.find(image[i]) < filename.size()) {
			std::cout<<i<<filename<<"<<<<<<<<<<<<<<<"<<std::endl;
			switch (i){
				case 6:
					type = "image/x-icon";
					break;
				case 7:
					type = "image/svg+xml";
					break;
				default:
					type = "image/" + image[i].substr(1);
			}
		return true;
	}}
	for (int i = 0; !audio[i].empty(); i++){
		if (filename.find(audio[i]) < filename.size()) {
			switch (i){
				case 6:
					type = "audio/x-ms-wma";
					break;
				default:
					type = "audio/" + audio[i].substr(1);
			}
		return true;
	}}
	for (int i = 0; !video[i].empty(); i++){
		if (filename.find(video[i]) < filename.size()) {
			switch (i){
				case 0:
					type = "video/mp4";
					break;
				case 1:
					type = "video/x-msvideo";
					break;
				case 2:
					type = "video/quicktime";
					break;
				case 3:
					type = "video/x-matroska";
					break;
				case 4:
					type = "video/x-ms-wmv";
					break;
				case 5:
					type = "video/x-flv";
					break;
			}
		return true;
	}}
	for (int i = 0; !exec[i].empty(); i++){
		if (filename.find(exec[i]) < filename.size()) {
			switch (i){
				case 0:
					type = "application/x-msdownload";
					break;
				case 1:
					type = "application/x-msdownload";
					break;
				default:
					type = "application/octet-stream";
					break;
			}
		return true;
	}}
	for (int i = 0; !compr[i].empty(); i++){
		if (filename.find(compr[i]) < filename.size()) {
			switch (i){
				case 0:
					type = "application/zip";
					break;
				case 1:
					type = "application/vnd.rar";
					break;
				case 2:
					type = "application/x-tar";
					break;
				case 3:
					type = "application/gzip";
					break;
				case 4:
					type = "application/x-7z-compressed";
					break;
				case 5:
					type = "application/x-bzip2";
					break;
			}
		return true;
	}}
	for (int i = 0; !doc[i].empty(); i++){
		if (filename.find(doc[i]) < filename.size()) {
			switch (i){
				case 0:
					type = "application/pdf";
					break;
				case 1:
					type = "application/msword";
					break;
				case 2:
					type = "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
					break;
				case 3:
					type = "application/vnd.ms-excel";
					break;
				case 4:
					type = "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
					break;
				case 5:
					type = "application/vnd.ms-powerpoint";
					break;
				case 6:
					type = "application/vnd.openxmlformats-officedocument.presentationml.presentation";
					break;
			}
		return true;
	}}
	for (int i = 0; !oth[i].empty(); i++){
		if (filename.find(oth[i]) < filename.size()) {
			switch (i){
				case 0:
					type = "image/vnd.adobe.photoshop";
					break;
				case 1:
					type = "application/x-iso9660-image";
					break;
				case 2:
					type = "application/octet-stream";
					break;
				case 3:
					type = "application/java-vm";
					break;
				case 4:
					type = "application/x-shockwave-flash";
					break;
				case 5:
					type = "font/ttf";
					break;
				case 6:
					type = "font/otf";
					break;
			}
		return true;
	}}
	if (filename.find(".html") < filename.size())
		type = "text/html";
	else
		type = "text/plain";
	return false;
}