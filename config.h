#include <unordered_map>
#include <string>
#include <fstream>

class Parser
{
public:
	struct Variable
	{
		int integer;
		__int64 integer64;
		float floating;
		bool boolean;
		std::string string;
	};

	Parser(const std::string& filename)
	{
		std::string line;
		std::ifstream ifile(filename);
		while (std::getline(ifile, line))
		{
			ParseLine(line);
		}
	}

	void ParseLine(const std::string& line)
	{
		std::string varName;
		const char* p = line.c_str();

		//parse variable name
		for (; *p; p++)
		{
			if (*p == '=')		break;
			else if (*p == ' ')	continue;
			else				varName += *p;
		}

		if (*p++ != '\0')
		{
			Variable var;
			var.string = std::string(p, strchr(p, ';') - p);

			// skip whitespaces
			while (*p == ' ' && *p)
				p++;

			var.integer = atoi(p);
			var.integer64 = _atoi64(p);
			var.boolean = var.integer > 0;
			var.floating = (float)atof(p);

			m_varMap[varName] = var;
		}
	}

	int GetInt(const std::string& varName)
	{
		auto it = m_varMap.find(varName);
		return (it != m_varMap.end()) ? (*it).second.integer : -1;
	}

	bool GetBool(const std::string& varName)
	{
		auto it = m_varMap.find(varName);
		return (it != m_varMap.end()) ? (*it).second.boolean : false;
	}

	__int64 GetInt64(const std::string& varName)
	{
		auto it = m_varMap.find(varName);
		return (it != m_varMap.end()) ? (*it).second.integer64 : -1;
	}

	float GetFloat(const std::string& varName)
	{
		auto it = m_varMap.find(varName);
		return (it != m_varMap.end()) ? (*it).second.floating : -1;
	}

	std::string GetString(const std::string& varName)
	{
		auto it = m_varMap.find(varName);
		return (it != m_varMap.end()) ? (*it).second.string : "";
	}

private:
	std::unordered_map<std::string, Variable> m_varMap;
};