#pragma once
#include "widgets/EventWidget.hpp"


namespace rack {


/** Caches a widget's draw() result to a framebuffer so it is called less frequently
When `dirty` is true, its children will be re-rendered on the next call to step() override.
Events are not passed to the underlying scene.
*/
struct FramebufferWidget : virtual EventWidget {
	/** Set this to true to re-render the children to the framebuffer the next time it is drawn */
	bool dirty = true;
	/** A margin in pixels around the children in the framebuffer
	This prevents cutting the rendered SVG off on the box edges.
	*/
	float oversample;
	/** The root object in the framebuffer scene
	The FramebufferWidget owns the pointer
	*/
	struct Internal;
	Internal *internal;

	FramebufferWidget();
	~FramebufferWidget();
	void draw(NVGcontext *vg) override;
	int getImageHandle();

	void on(event::Zoom &e) override {
		dirty = true;
		EventWidget::on(e);
	}
};


} // namespace rack
