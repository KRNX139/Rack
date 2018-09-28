#include "app.hpp"


namespace rack {


SVGKnob::SVGKnob() {
	shadow = new CircularShadow();
	addChild(shadow);
	shadow->box.size = math::Vec();

	tw = new TransformWidget();
	addChild(tw);

	sw = new SVGWidget();
	tw->addChild(sw);
}

void SVGKnob::setSVG(std::shared_ptr<SVG> svg) {
	sw->setSVG(svg);
	tw->box.size = sw->box.size;
	box.size = sw->box.size;
	shadow->box.size = sw->box.size;
	shadow->box.pos = math::Vec(0, sw->box.size.y * 0.1);
	// shadow->box = shadow->box.grow(math::Vec(2, 2));
}

void SVGKnob::step() {
	// Re-transform TransformWidget if dirty
	if (dirty) {
		float angle;
		if (std::isfinite(minValue) && std::isfinite(maxValue)) {
			angle = math::rescale(value, minValue, maxValue, minAngle, maxAngle);
		}
		else {
			angle = math::rescale(value, -1.0, 1.0, minAngle, maxAngle);
			angle = std::fmod(angle, 2*M_PI);
		}
		tw->identity();
		// Rotate SVG
		math::Vec center = sw->box.getCenter();
		tw->translate(center);
		tw->rotate(angle);
		tw->translate(center.neg());
	}
	FramebufferWidget::step();
}

void SVGKnob::on(event::Change &e) {
	dirty = true;
	ParamWidget::on(e);
}


} // namespace rack
