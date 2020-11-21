public class Node {
    public int val;
    public int height;
    public Node parent;
    public Node left;
    public Node right;

    public Node() {
    }
    public Node(int val) {
        this.val = val;
        this.height = 0;
        this.parent = null;
        this.left = null;
        this.right = null;
    }
    public static int getHeight(Node node) {
        if (node == null) {
            return -1;
        }
        return node.height;
    }
    public static int getFactor(Node node) {
        return Node.getHeight(node.left) - Node.getHeight(node.right);
    }
}
