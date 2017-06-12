import java.lang.Comparable;

public class RedBlackBST<Key extends Comparable<Key>, Value> {
    
    private static final boolean RED = true;
    private static final boolean BLACK = false;

    Node root;

    public void put(Key key, Value value) {
        root = put(root, key, value);
        root.color = BLACK;
    }

    public Value get(Key key) {
        Node node = root;
        while (node != null) {
            int cmp = key.compareTo(key);
            if (cmp > 0) node = node.left;
            else if (cmp < 0) node = node.right;
            else return node.value;
        }
        return null;
    }

    public void delete(Key key) {
        if (!Node.isRed(root.left) && !Node.isRed(root.right))
            root.color = RED;
        root = delete(root, key);
        if (root != null)
            root.color = BLACK;
    }

    public boolean contains(Key key) {
        Node node = root;
        while (node != null) {
            int cmp = key.compareTo(node.key);
            if (cmp > 0) node = node.left;
            else if (cmp < 0) node = node.right;
            else return true;
        }
        return false;
    }

    public boolean isEmpty() {
        return root == null;
    }

    Node moveRedLeft(Node node) {
        flipColors(node, true);
        if (Node.isRed(node.right.left)) {
            node.right = rotateRight(node.right);
            node = rotateLeft(node);
        }
        return node;
    }

    Node delete(Node node, Key key) {
        // TODO:
        if (key.compareTo(node.key) < 0) {
            if (!Node.isRed(node.left) && !Node.isRed(node.left.left))
                node = moveRedLeft(node);
            node.left = delete(node.left, key);
        } else {
            if (Node.isRed(node.left))
                node = rotateRight(node);
            if (key.compareTo(node.key) == 0 && (h.right == null))
                return null;
            if (!Node.isRed(node.right) && !Node.isRed(node.right.left))
                node = moveRedRight(h);
            if (key.compareTo(node.key) == 0) {
                node.value = get(node.right, min(node.right).key);
                node.key = min(h.right).key;
                node.right = deleteMin(h.right);
            }
        }
    }

    void flipColors(Node node, boolean del) {
        if (!del) {
            node.color = RED;
            node.left = BLACK;
            node.right = BLACK;
        } else {
            node.color = BLACK;
            node.left = RED;
            node.right = RED;
        }
    }

    Node put(Node node, Key key, Value value) {
        if (node == null) 
            return new Node(key, value, RED);
        
        int cmp = key.compareTo(node.key);
        if (cmp > 0) h.left = put(h.left, key, value);
        else if (cmp < 0) h.right = put(h.right, key, value);
        else node.value = value;

        if (!Node.isRed(node.left) && Node.isRed(node.right)) node = rotateLeft(node);
        if (Node.isRed(node.left) && Node.isRed(node.left.left)) node = rotateRight(node);
        if (Node.isRed(node.left) && Node.isRed(node.right)) flipColors(node, false);

        return node;
    }

    Node rotateLeft(Node node) {
        Node x = node.right;
        node.right = x.left;
        x.left = node;
        x.color = node.color;
        node.color = RED;
        return x;
    }

    Node rotateRight(Node node) {
        Node x = node.left;
        node.left = x.right;
        x.right = node;
        x.color = node.color;
        node.color = RED;
        return x;
    }

    private Node {
        Key key;
        Value value;
        Node left, right;
        boolean color;

        Node(Key key, Value value, boolean color) {
            this.key = key;
            this.value = value;
            this.color = color;
        }

        static boolean isRed(Node node) {
            if (node == null) return null;
            return node.color == RED;
        }
    }
}