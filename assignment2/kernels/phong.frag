// phong.frag

/*
  This fragment implements the Phong Reflection model.
*/

varying vec3 modelPos;    // fragment position in model space
varying vec3 lightSourcePos; // light source position in model space
varying vec3 lightSourcePos1;
varying vec3 normal;	  // fragment normal in model space

void main()
{
    vec3 C = vec3(0.0, 0.0, 0.0); // camera position

    vec3 lightAmbient  = gl_LightSource[0].ambient.xyz;
    vec3 lightDiffuse0  = gl_LightSource[0].diffuse.xyz;
    vec3 lightSpecular0 = gl_LightSource[0].specular.xyz;
    
    vec3 lightDiffuse1  = gl_LightSource[1].diffuse.xyz;
    vec3 lightSpecular1 = gl_LightSource[1].specular.xyz;

    vec3 materialAmbient = gl_FrontMaterial.ambient.xyz;
	vec3 materialDiffuse = gl_FrontMaterial.diffuse.xyz;
    vec3 materialSpecular  = gl_FrontMaterial.specular.xyz;
    float shininess    = gl_FrontMaterial.shininess;

	/* CS 148 TODO: Implement the Phong reflectance model here */
	vec3 Lm0 = normalize(lightSourcePos-modelPos);
	vec3 Rm0 = normalize(reflect(-Lm0,normal));
    vec3 Lm1 = normalize(lightSourcePos1-modelPos);
    vec3 Rm1 = normalize(reflect(-Lm1,normal));
	vec3 V = normalize(-modelPos);

	vec3 colorAmbient = materialAmbient*lightAmbient;
	vec3 colorDiffuse0 = clamp(max(dot(Lm0,normal),0.0)*materialDiffuse*lightDiffuse0,0.0,1.0);
    vec3 colorSpecular0 = clamp(pow(max(dot(Rm0,V),0.0),shininess)*materialSpecular*lightSpecular0,0.0,1.0);
    vec3 colorDiffuse1 = clamp(max(dot(Lm1,normal),0.0)*materialDiffuse*lightDiffuse1,0.0,1.0);
    vec3 colorSpecular1 = clamp(pow(max(dot(Rm1,V),0.0),shininess)*materialSpecular*lightSpecular1,0.0,1.0);

	vec3 color = colorAmbient + colorDiffuse0 + colorSpecular0 + colorDiffuse1 + colorSpecular1;
	color = clamp(color, 0.0, 1.0);

    gl_FragColor = vec4(color, 1.0);
}
