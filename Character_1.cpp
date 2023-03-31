class Character{
    private:
        std::string name;
    public:
        Character(std::string name);
        void circle(float rad, float xx, float yy);
        void head();
        void neck();
        void body();
        void leftHand();
        void rightHand();
        void leftArm();
        void rightArm();
        void leftLeg();
        void rightLeg();
        void leftShin();
        void rightShin();
        void leftHand_2();
        void rightHand_2();
        void bodyMovement_2();
        void leftHandMovement();
        void rightHandMovement();
        void leftLegMovement();
        void rightLegMovement();
        void angleTheta();
        void drawStickman_2();
        void blackBG();
};

void Character::circle(float rad, float xx, float yy) {

	float thetha = 2 * 3.1415 / 20;
	float x, y;
	glColor3f(1.1, 1.1, 1.10);
	glLineWidth(1.0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 20; i++) {
		x = rad * cos(i*thetha) + xx;
		y = rad*sin(i*thetha) + yy;
		float z = -5.0f;
		glVertex3f(x,y,z);
	}
	glEnd();
}

void Character::head() {//stickman head
	circle(0.08, -1.0f, 0.97f);

}

void Character::neck() {//stickman neck
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(1.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-1.0f, 0.9f, -5.0f);
	glVertex3f(-1.0f, 0.8f, -5.0f);
	glEnd();
}

void Character::body() { //stickman body
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(1.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-1.0f,0.8f,-5.0f);
	glVertex3f(-1.0f, 0.5f,-5.0f);
	glEnd();
}

void Character::leftHand() {//stickman1 left hand
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(1.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-1.0f, 0.8f, -5.0f);
	glVertex3f(-0.9f, 0.7f, -5.0f);
	glEnd();
}

void Character::rightHand() { //stick man 1 right hand

	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(1.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-1.0f, 0.8f, -5.0f);
	glVertex3f(-0.89f, 0.75f, -5.0f);
	glEnd();
}
void Character::leftArm() {
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(1.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-0.89f, 0.75f, -5.0f);
	glVertex3f(-0.79f, 0.80f, -5.0f);
	glEnd();
}

void Character::rightArm() {
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(1.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-0.9f, 0.7f, -5.0f);
	glVertex3f(-0.79f, 0.80f, -5.0f);
	glEnd();
}

void Character::leftLeg() {
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(1.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-1.0f, 0.5f, -5.0f);
	glVertex3f(-1.01f, 0.4f, -5.0f);
	glEnd();
}

void Character::rightLeg() {
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(1.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-1.0f, 0.5f, -5.0f);
	glVertex3f(-0.99f, 0.4f, -5.0f);
	glEnd();
}

void Character::leftShin() {
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(1.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-1.0f, 0.4f, -5.0f);
	glVertex3f(-1.01f, 0.3f, -5.0f);
	glEnd();
}

void Character::rightShin() {
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(1.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-1.0f, 0.4f, -5.0f);
	glVertex3f(-0.99f, 0.3f, -5.0f);
	glEnd();
}

void Character::leftHand_2() {
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(1.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-1.0f, 0.8f, -5.0f);
	glVertex3f(-1.01f, 0.6f, -5.0f);
	glEnd();
}

void Character::rightHand_2() {
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(1.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-1.0f, 0.8f, -5.0f);
	glVertex3f(-0.99f, 0.6f, -5.0f);
	glEnd();
}

void Character::bodyMovement_2() {
	if (counter < 19400) {
		glTranslatef(tx_2, 0.0, 0.0);
		counter++;
	} else {
		glTranslatef(tx_2, 0.0, 0.0);
		tx_2 = tx_2-backwardIncrmt;
	}

}

void Character::leftHandMovement() {
	glTranslatef(-1.0, 0.8, -5.0);
	glRotatef(movTheta, 0.0, 0.0, 1.0);
	glTranslatef(1.0, -0.8, 5.0);
}


void Character::rightHandMovement() //stick man 2 right hand movement
{
	glTranslatef(-1.0f, 0.8f, -5.0f);
	glRotatef(-movTheta, 0.0f, 0.0f, 1.0f);
	glTranslatef(1.0f, -0.8f, 5.0f);
}

//leg movement
void Character::leftLegMovement()
{
	glTranslatef(-1.0, 0.5, -5.0);
	glRotatef(-movTheta, 0.0, 0.0, 1.0);
	glTranslatef(1.0, -0.5, 5.0);
}

void Character::rightLegMovement()
{
	glTranslatef(-1.0f, 0.5f, -5.0f);
	glRotatef(movTheta, 0.0, 0.0, 1.0);
	glTranslatef(1.0f, -0.5f, 5.0f);

}

void Character::angleTheta() {
	if (forwardMov) {
		movTheta += incTheta;
		if (movTheta > maxTheta)
			forwardMov = false;
	} else if (!forwardMov) {
		movTheta -= incTheta;
		if (movTheta < -maxTheta)

			forwardMov = true;
	}
}

void Character::drawStickman_2() {
	//body
	glPushMatrix();
	bodyMovement_2();
	body();
	head();
	neck();
	glPopMatrix();
	
	//leftHand
	glPushMatrix();
	bodyMovement_2();
	leftHandMovement();
	leftHand_2();
	glPopMatrix();

	//rightHand
	glPushMatrix();
	bodyMovement_2();
	rightHandMovement();
	rightHand_2();
	glPopMatrix();

	//leftLeg
	glPushMatrix();
	bodyMovement_2();
	leftLegMovement();
	leftLeg();
	leftShin();
	glPopMatrix();

	//rightLeg
	glPushMatrix();
	bodyMovement_2();
	rightLegMovement();
	rightLeg();
	rightShin();
	glPopMatrix();

	angleTheta();
}

void Character::blackBG() {
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0f, -3.80f, -5.0f);
    glVertex3f(5.0f, -3.80f, -5.0f);
    glVertex3f(5.0f, 4.5f, -5.0f);
    glVertex3f(-5.0f, 4.5f,-5.0f);
    glEnd();
}