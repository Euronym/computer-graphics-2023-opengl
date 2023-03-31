class Gun{
    private:
        int nBullets;
    public:
        Gun(int nBullets) {
            this->nBullets = nBullets;
        }
        void shoot() {
            nBullets -= 1;
        }
};