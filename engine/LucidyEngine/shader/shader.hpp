#ifndef SHADER_HPP
#define SHADER_HPP

#include "../generic/graphic_lib.hpp"

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>
#include <unordered_map>

namespace ly{

	class Shader {
	public:
		Shader();
		~Shader();
		void addFile( const std::string& filePath, enum_t shaderType );
		void init();

		void bind() const;
		void unbind() const;

		void setUniform1i( const std::string& name, int_t value );
		void setUniform1f(const std::string& name, float_t value);
		void setUniform4f( const std::string& name, vec4_t value );
		void setUniformMat4f( const std::string& name, const mat4_t& value );

	private:
		uint_t renderId;
		std::unordered_map<std::string, int_t> uniformLocationCache;

		std::vector<enum_t> shaderTypes;
		std::vector<uint_t> shaderNums;
		std::vector<std::string> shaderData;

		uint_t compileShader( uint_t type, const std::string& source );
		int_t getUniformLocation( const std::string& name);

	};

}

#endif // SHADER_HPP
