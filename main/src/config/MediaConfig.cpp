#include "MediaConfig.h"

#include "config/utils.h"

using namespace webserv;
using namespace webserv::config;

std::istream& operator>>(std::istream& source, webserv::config::MediaConfig& config)
{
	std::string line;
	while (utils::getLine(source, line))
	{
		if (utils::isIgnored(line))
			continue;
		else if (utils::isBlockEnd(line))
			break;

		const std::vector<std::string> words = utils::breakLine(line);
		if (words.size() != 2)
			throw ParsingException("Invalid line structure: " + line);

		config._fileExtensionToMediaType[words[0]] = MediaType(words[1]);
	}

	return source;
}

MediaConfig MediaConfig::makeDefault()
{
	MediaConfig config;

	config._fileExtensionToMediaType[".html"] = "text/html";
	config._fileExtensionToMediaType[".htm"] = "text/html";
	config._fileExtensionToMediaType[".shtml"] = "text/html";
	config._fileExtensionToMediaType[".css"] = "text/css";
	config._fileExtensionToMediaType[".xml"] = "text/xml";
	config._fileExtensionToMediaType[".gif"] = "image/gif";
	config._fileExtensionToMediaType[".jpeg"] = "image/jpeg";
	config._fileExtensionToMediaType[".jpg"] = "image/jpeg";
	config._fileExtensionToMediaType[".js"] = "application/javascript";
	config._fileExtensionToMediaType[".atom"] = "application/atom+xml";
	config._fileExtensionToMediaType[".rss"] = "application/rss+xml";

	config._fileExtensionToMediaType[".mml"] = "text/mathml";
	config._fileExtensionToMediaType[".txt"] = "text/plain";
	config._fileExtensionToMediaType[".jad"] = "text/vnd.sun.j2me.app-descriptor";
	config._fileExtensionToMediaType[".wml"] = "text/vnd.wap.wml";
	config._fileExtensionToMediaType[".htc"] = "text/x-component";

	config._fileExtensionToMediaType[".png"] = "image/png";
	config._fileExtensionToMediaType[".svg"] = "image/svg+xml";
	config._fileExtensionToMediaType[".svgz"] = "image/svg+xml";
	config._fileExtensionToMediaType[".tif"] = "image/tiff";
	config._fileExtensionToMediaType[".tiff"] = "image/tiff";
	config._fileExtensionToMediaType[".wbmp"] = "image/vnd.wap.wbmp";
	config._fileExtensionToMediaType[".webp"] = "image/webp";
	config._fileExtensionToMediaType[".ico"] = "image/x-icon";
	config._fileExtensionToMediaType[".jng"] = "image/x-jng";
	config._fileExtensionToMediaType[".bmp"] = "image/x-ms-bmp";

	config._fileExtensionToMediaType[".woff"] = "font/woff";
	config._fileExtensionToMediaType[".woff2"] = "font/woff2";

	config._fileExtensionToMediaType[".jar"] = "application/java-archive";
	config._fileExtensionToMediaType[".war"] = "application/java-archive";
	config._fileExtensionToMediaType[".ear"] = "application/java-archive";
	config._fileExtensionToMediaType[".json"] = "application/json";
	config._fileExtensionToMediaType[".hqx"] = "application/mac-binhex40";
	config._fileExtensionToMediaType[".doc"] = "application/msword";
	config._fileExtensionToMediaType[".pdf"] = "application/pdf";
	config._fileExtensionToMediaType[".ps"] = "application/postscript";
	config._fileExtensionToMediaType[".eps"] = "application/postscript";
	config._fileExtensionToMediaType[".ai"] = "application/postscript";
	config._fileExtensionToMediaType[".rtf"] = "application/rtf";
	config._fileExtensionToMediaType[".m3u8"] = "application/vnd.apple.mpegurl";
	config._fileExtensionToMediaType[".kml"] = "application/vnd.google-earth.kml+xml";
	config._fileExtensionToMediaType[".kmz"] = "application/vnd.google-earth.kmz";
	config._fileExtensionToMediaType[".xls"] = "application/vnd.ms-excel";
	config._fileExtensionToMediaType[".eot"] = "application/vnd.ms-fontobject";
	config._fileExtensionToMediaType[".ppt"] = "application/vnd.ms-powerpoint";
	config._fileExtensionToMediaType[".odg"] = "application/vnd.oasis.opendocument.graphics";
	config._fileExtensionToMediaType[".odp"] = "application/vnd.oasis.opendocument.presentation";
	config._fileExtensionToMediaType[".ods"] = "application/vnd.oasis.opendocument.spreadsheet";
	config._fileExtensionToMediaType[".odt"] = "application/vnd.oasis.opendocument.text";

	config._fileExtensionToMediaType[".pptx"] = "application/vnd.openxmlformats-officedocument.presentationml.presentation";
	config._fileExtensionToMediaType[".xlsx"] = "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
	config._fileExtensionToMediaType[".docx"] = "application/vnd.openxmlformats-officedocument.wordprocessingml.document";

	config._fileExtensionToMediaType[".wmlc"] = "application/vnd.wap.wmlc";
	config._fileExtensionToMediaType[".7z"] = "application/x-7z-compressed";
	config._fileExtensionToMediaType[".cco"] = "application/x-cocoa";
	config._fileExtensionToMediaType[".jardiff"] = "application/x-java-archive-diff";
	config._fileExtensionToMediaType[".jnlp"] = "application/x-java-jnlp-file";
	config._fileExtensionToMediaType[".run"] = "application/x-makeself";
	config._fileExtensionToMediaType[".pl"] = "application/x-perl";
	config._fileExtensionToMediaType[".pm"] = "application/x-perl";
	config._fileExtensionToMediaType[".prc"] = "application/x-pilot";
	config._fileExtensionToMediaType[".pdb"] = "application/x-pilot";
	config._fileExtensionToMediaType[".rar"] = "application/x-rar-compressed";
	config._fileExtensionToMediaType[".rpm"] = "application/x-redhat-package-manager";
	config._fileExtensionToMediaType[".sea"] = "application/x-sea";
	config._fileExtensionToMediaType[".swf"] = "application/x-shockwave-flash";
	config._fileExtensionToMediaType[".sit"] = "application/x-stuffit";
	config._fileExtensionToMediaType[".tcl"] = "application/x-tcl";
	config._fileExtensionToMediaType[".tk"] = "application/x-tcl";
	config._fileExtensionToMediaType[".der"] = "application/x-x509-ca-cert";
	config._fileExtensionToMediaType[".pem"] = "application/x-x509-ca-cert";
	config._fileExtensionToMediaType[".crt"] = "application/x-x509-ca-cert";
	config._fileExtensionToMediaType[".xpi"] = "application/x-xpinstall";
	config._fileExtensionToMediaType[".xhtml"] = "application/xhtml+xml";
	config._fileExtensionToMediaType[".xspf"] = "application/xspf+xml";
	config._fileExtensionToMediaType[".zip"] = "application/zip";

	config._fileExtensionToMediaType[".bin"] = "application/octet-stream";
	config._fileExtensionToMediaType[".exe"] = "application/octet-stream";
	config._fileExtensionToMediaType[".dll"] = "application/octet-stream";
	config._fileExtensionToMediaType[".deb"] = "application/octet-stream";
	config._fileExtensionToMediaType[".dmg"] = "application/octet-stream";
	config._fileExtensionToMediaType[".iso"] = "application/octet-stream";
	config._fileExtensionToMediaType[".img"] = "application/octet-stream";
	config._fileExtensionToMediaType[".msi"] = "application/octet-stream";
	config._fileExtensionToMediaType[".msp"] = "application/octet-stream";
	config._fileExtensionToMediaType[".msm"] = "application/octet-stream";

	config._fileExtensionToMediaType[".mid"] = "audio/midi";
	config._fileExtensionToMediaType[".midi"] = "audio/midi";
	config._fileExtensionToMediaType[".kar"] = "audio/midi";
	config._fileExtensionToMediaType[".mp3"] = "audio/mpeg";
	config._fileExtensionToMediaType[".ogg"] = "audio/ogg";
	config._fileExtensionToMediaType[".m4a"] = "audio/x-m4a";
	config._fileExtensionToMediaType[".ra"] = "audio/x-realaudio";

	config._fileExtensionToMediaType[".3gpp"] = "video/3gpp";
	config._fileExtensionToMediaType[".3gp"] = "video/3gpp";
	config._fileExtensionToMediaType[".ts"] = "video/mp2t";
	config._fileExtensionToMediaType[".mp4"] = "video/mp4";
	config._fileExtensionToMediaType[".mpeg"] = "video/mpeg";
	config._fileExtensionToMediaType[".mpg"] = "video/mpeg";
	config._fileExtensionToMediaType[".mov"] = "video/quicktime";
	config._fileExtensionToMediaType[".webm"] = "video/webm";
	config._fileExtensionToMediaType[".flv"] = "video/x-flv";
	config._fileExtensionToMediaType[".m4v"] = "video/x-m4v";
	config._fileExtensionToMediaType[".mng"] = "video/x-mng";
	config._fileExtensionToMediaType[".asx"] = "video/x-ms-asf";
	config._fileExtensionToMediaType[".asf"] = "video/x-ms-asf";
	config._fileExtensionToMediaType[".wmv"] = "video/x-ms-wmv";
	config._fileExtensionToMediaType[".avi"] = "video/x-msvideo";

	return config;
}

const std::unordered_map<std::string, MediaType>& MediaConfig::fileExtensionToMediaType() const
{
	return _fileExtensionToMediaType;
}
