#include "LVGLColorPicker.h"

#include "LVGLObject.h"
#include "properties/LVGLPropertyColor.h"

#include <QIcon>

class LVGLPropertyCPickerType : public LVGLPropertyEnum
{
public:
	LVGLPropertyCPickerType()
		: LVGLPropertyEnum(QStringList() << "Rectange" << "Disc")
	{}

	QString name() const { return "Type"; }

protected:
	int get(LVGLObject *obj) const {
		lv_cpicker_ext_t *ext = reinterpret_cast<lv_cpicker_ext_t *>(lv_obj_get_ext_attr(obj->obj()));
		return ext->type;
	}
	void set(LVGLObject *obj, int index) { lv_cpicker_set_type(obj->obj(), index & 0xff); }
};

class LVGLPropertyCPickerHue : public LVGLPropertyInt
{
public:
	LVGLPropertyCPickerHue() : LVGLPropertyInt(0, 360) {}

	QString name() const { return "Hue"; }

protected:
	int get(LVGLObject *obj) const { return lv_cpicker_get_hue(obj->obj()); }
	void set(LVGLObject *obj, int value) { lv_cpicker_set_hue(obj->obj(), static_cast<uint16_t>(value)); }
};

class LVGLPropertyCPickerSaturation : public LVGLPropertyInt
{
public:
	LVGLPropertyCPickerSaturation() : LVGLPropertyInt(0, 100) {}

	QString name() const { return "Saturation"; }

protected:
	int get(LVGLObject *obj) const { return lv_cpicker_get_saturation(obj->obj()); }
	void set(LVGLObject *obj, int value) { lv_cpicker_set_saturation(obj->obj(), static_cast<uint8_t>(value)); }
};

class LVGLPropertyCPickerValue : public LVGLPropertyInt
{
public:
	LVGLPropertyCPickerValue() : LVGLPropertyInt(0, 100) {}

	QString name() const { return "Value"; }

protected:
	int get(LVGLObject *obj) const { return lv_cpicker_get_value(obj->obj()); }
	void set(LVGLObject *obj, int value) { lv_cpicker_set_value(obj->obj(), static_cast<uint8_t>(value)); }
};

class LVGLPropertyCPickerMode : public LVGLPropertyEnum
{
public:
	LVGLPropertyCPickerMode()
		: LVGLPropertyEnum(QStringList() << "Hue" << "Saturation" << "Value")
	{}

	QString name() const { return "Color mode"; }

protected:
	int get(LVGLObject *obj) const { return lv_cpicker_get_color_mode(obj->obj()); }
	void set(LVGLObject *obj, int index) { lv_cpicker_set_color_mode(obj->obj(), index & 0xff); }
};

class LVGLPropertyCPickerColor : public LVGLPropertyColor
{
public:
	QString name() const { return "Color"; }

protected:
	lv_color_t get(LVGLObject *obj) const { return lv_cpicker_get_color(obj->obj()); }
	void set(LVGLObject *obj, lv_color_t boolean) { lv_cpicker_set_color(obj->obj(), boolean); }
};

LVGLColorPicker::LVGLColorPicker()
{
	m_properties << new LVGLPropertyCPickerType;
	m_properties << new LVGLPropertyCPickerHue;
	m_properties << new LVGLPropertyCPickerSaturation;
	m_properties << new LVGLPropertyCPickerValue;
	m_properties << new LVGLPropertyCPickerMode;
	m_properties << new LVGLPropertyBool("Indicator Colored", "lv_cpicker_set_indic_colored", lv_cpicker_set_indic_colored, lv_cpicker_get_indic_colored);
	m_properties << new LVGLPropertyBool("Preview", "lv_cpicker_set_preview", lv_cpicker_set_preview, lv_cpicker_get_preview);
	m_properties << new LVGLPropertyCPickerColor;

	m_editableStyles << LVGL::StyleParts(LVGL::Body | LVGL::Line); // LV_CPICKER_STYLE_MAIN
	m_editableStyles << LVGL::Body; // LV_CPICKER_STYLE_INDICATOR
}

QString LVGLColorPicker::name() const
{
	return "Color picker";
}

QString LVGLColorPicker::className() const
{
	return "lv_cpicker";
}

LVGLWidget::Type LVGLColorPicker::type() const
{
	return ColorPicker;
}

QIcon LVGLColorPicker::icon() const
{
	return QIcon();
}

QSize LVGLColorPicker::minimumSize() const
{
	return QSize(100, 100);
}

lv_obj_t *LVGLColorPicker::newObject(lv_obj_t *parent) const
{
	lv_obj_t *obj = lv_cpicker_create(parent, nullptr);
	//for (const LVGLProperty &p:m_properties)
	//	p.set(obj, p.defaultVal);
	return obj;
}

QStringList LVGLColorPicker::styles() const
{
	return QStringList() << "LV_CPICKER_STYLE_MAIN"
								<< "LV_CPICKER_STYLE_INDICATOR";
}

lv_style_t *LVGLColorPicker::style(lv_obj_t *obj, int type) const
{
	return const_cast<lv_style_t*>(lv_cpicker_get_style(obj, type & 0xff));
}

void LVGLColorPicker::setStyle(lv_obj_t *obj, int type, lv_style_t *style) const
{
	lv_cpicker_set_style(obj, static_cast<lv_cpicker_style_t>(type), style);
}

lv_style_t *LVGLColorPicker::defaultStyle(int type) const
{
	if (type == LV_CPICKER_STYLE_MAIN)
		return &lv_style_plain;
	else if (type == LV_CPICKER_STYLE_INDICATOR)
		return &lv_style_plain;
	return nullptr;
}
