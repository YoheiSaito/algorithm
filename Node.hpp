namespace teyo{
	enum Color {
		BLACK,
		RED
	};
	template <class T> class Node{
		protected:
		Color color;
		Node<T> *root;
		Node<T> *left, *right;
		unsigned int count;
		public:
		const T key;
		Node(T key_, Color color_ = Color::BLACK):
			key(key_)
		{
			color = color_;
			root = NULL;
			left = NULL;
			right = NULL;
			count = 1;
		}
		Node(T key_, Node<T> *root, Color color_ = Color::BLACK):
			key(key_)
		{
			color = color_;
			this->root = root;
			this->left = NULL;
			this->right = NULL;
			count = 1;
		}
		Node(T key_, Node<T> *left, Node<T> *right, Color color_ = Color::BLACK):
			key(key_)
		{
			color = color_;
			this->root = NULL;
			this->left = left;
			this->right = right;
			count = 1;
		}

		Node(T key_, Node<T> *root, Node<T> *left, Node<T> *right, Color color_ = Color::BLACK):
			key(key_)
		{
			color = color_;
			this->root = root;
			this->left = left;
			this->right = right;
			count = 1;
		}


		void setLeft(Node<T> *left){
			this->left = left;
		}
		void setRight(Node<T> *right){
			this->right = right;
		}
		void setRoot(Node<T> *root){
			this->root = root;
		}

		virtual Node<T>* getLeft(void){
			return this->left;
		}
		virtual Node<T>* getRight(void){
			return this->right;
		}
		virtual Node<T>* getRoot(void){
			return this->root;
		}
		T getKey(){
			return this->key;
		}
		void countup(void){
			count++;
		}
		void countdown(void){
			count--;
		}
		unsigned int getCount(void){
			return count;
		}
		Color getColor(){
			return color;
		}
		void setColor(Color c){
			color = c;
		}

	};


}
