#include "engine/Module.hpp"


namespace rack {


json_t *Module::toJson() {
	json_t *rootJ = json_object();

	// params
	json_t *paramsJ = json_array();
	for (Param &param : params) {
		json_t *paramJ = param.toJson();
		json_array_append_new(paramsJ, paramJ);
	}
	json_object_set_new(rootJ, "params", paramsJ);

	// data
	json_t *dataJ = dataToJson();
	if (dataJ) {
		json_object_set_new(rootJ, "data", dataJ);
	}

	return rootJ;
}

void Module::fromJson(json_t *rootJ) {
	// params
	json_t *paramsJ = json_object_get(rootJ, "params");
	size_t i;
	json_t *paramJ;
	json_array_foreach(paramsJ, i, paramJ) {
		uint32_t paramId = i;
		// Get paramId
		json_t *paramIdJ = json_object_get(paramJ, "paramId");
		if (paramIdJ) {
			// Legacy v0.6.0 to <v1.0
			paramId = json_integer_value(paramIdJ);
		}

		if (paramId < params.size()) {
			params[paramId].fromJson(paramJ);
		}
	}

	// data
	json_t *dataJ = json_object_get(rootJ, "data");
	if (dataJ) {
		dataFromJson(dataJ);
	}
}


} // namespace rack
