package com.yegorov.alexey.elements.compass;

import com.yegorov.alexey.elements.api.ElementsCompass;

public class Compass {

    private int compassID;

    public Compass(Object manager) {

        compassID = ElementsCompass.create(manager);
    }

    public boolean close() {

        return ElementsCompass.destroy(compassID);
    }

    public boolean startup(int width, int height) {

        return ElementsCompass.startup(compassID, width, height);
    }

    public boolean render() {

        return ElementsCompass.render(compassID);
    }

    public boolean rotation(float omega) {

        return ElementsCompass.rotation(compassID, (float)Math.toRadians(omega));
    }

}
