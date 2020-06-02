#include "shader.hpp"

namespace ly{

	Shader::Shader() {}

	Shader::~Shader() {
		unbind();
	}

	void Shader::addFile( const std::string& filePath, enum_t shaderType ) {
		std::ifstream file( filePath );
		if( file.is_open() ){
			std::string shader(
				(std::istreambuf_iterator<char>( file )),
				(std::istreambuf_iterator<char>()) 
			);
			file.close();
			shaderData.push_back( shader );
			shaderTypes.push_back( shaderType );
		}else{
			std::cerr << "Unable to to find/open file " << filePath << " !" << std::endl; 
			file.close();
			return;
		}
	}

	void Shader::init() {
		GLCALL( renderId = glCreateProgram() );

		for ( uint_t i = 0; i < shaderData.size(); i++ ) {
			uint_t id = compileShader( shaderTypes[i], shaderData[i] );
			shaderNums.push_back( id );
		}

		for ( uint_t j = 0; j < shaderNums.size(); j++ ) {
			GLCALL( glAttachShader( renderId, shaderNums[ j ] ) );
		}

		GLCALL( glLinkProgram( renderId ) );
		GLCALL( glValidateProgram( renderId ) );

		for ( uint_t k = 0; k < shaderNums.size(); k++ ) {
			GLCALL( glDeleteShader( shaderNums[ k ] ) );
		}
	}

	void Shader::bind() const {
		GLCALL( glUseProgram( renderId ) );
	}

	void Shader::unbind() const {
		GLCALL( glDeleteProgram( renderId ) );
	}

	void Shader::setUniform1i( const std::string& name, int_t value ) {
		GLCALL( glUniform1i( getUniformLocation( name ), value ) );
	}

	void Shader::setUniform1f( const std::string& name, float_t value ) {
		GLCALL( glUniform1f( getUniformLocation( name ), value ) );
	}

	void Shader::setUniform4f( const std::string& name, vec4_t value ) {
		GLCALL( glUniform4f( getUniformLocation( name ), value.x, value.y, value.z, value.w ) );
	}


	void Shader::setUniformMat4f( const std::string& name, const mat4_t& value ) {
		GLCALL( glUniformMatrix4fv( getUniformLocation( name ), 1, GL_FALSE, &value[0][0] ) );
	}

	uint_t Shader::compileShader( enum_t type, const std::string& source ) {
		GLCALL( uint_t id = glCreateShader( type ) );
		const char* src = source.c_str();
		GLCALL( glShaderSource( id, 1, &src, nullptr ) );
		GLCALL( glCompileShader( id ) );

		int_t result;
		GLCALL( glGetShaderiv( id, GL_COMPILE_STATUS, &result ) );
		if ( result == GL_FALSE ) {
			int_t length;
			GLCALL( glGetShaderiv( id, GL_INFO_LOG_LENGTH, &length ) );
			char* msg = new char[ length ];
			GLCALL( glGetShaderInfoLog( id, length, &length, msg ) );
			std::cerr
				<< "[OpenGL Error] (Error compiling " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader) \r\n" 
				<< "\t Message: " << msg << std::endl;
			GLCALL( glDeleteShader( id ) );
			delete[] msg;
			return 0;
		}

		return id;
	}

	int_t Shader::getUniformLocation( const std::string& name ) {
		if ( uniformLocationCache.find( name ) != uniformLocationCache.end() ) {
			return uniformLocationCache[ name ];
		}

		GLCALL( int_t location = glGetUniformLocation( renderId, name.c_str() ) );
		if ( location == -1 ) {
			std::cout << "[Shader Warning] (Uniform with name'" << name << "' does not exist)" << std::endl;
		}
		
		uniformLocationCache[ name ] = location;
		return location;
	}

}
