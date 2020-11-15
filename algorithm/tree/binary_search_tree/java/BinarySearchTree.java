import java.util.Arrays;
import java.util.Random;

public class BinarySearchTree {
    public static void main(String[] args) {
        if (args.length < 1) {
            return;
        }
        int MAX = 300;
        int len = Integer.parseInt(args[0]);
        if (len >= MAX) {
            return;
        }
        int[] nums = new int[len];
        Random random = new Random();
        BinarySearchTree bsTree = new BinarySearchTree();
        for (int i = 0; i < len;) {
            int val = random.nextInt(MAX);
            if (bsTree.insert(val)) {
                nums[i] = val;
                i++;
            }
        }
        System.out.println(Arrays.toString(nums));
        BinaryTree.inorderVisit(bsTree.root);

        for (int i = 0; i < len; i++) {
            bsTree.remove(nums[i]);
            BinaryTree.inorderVisit(bsTree.root);
        }
    }
    public Node root;
    public boolean insert(int val) {
        Node cur = root;
        Node parent = null;
        while (cur != null) {
            if (cur.val == val) {
                return false;
            }
            parent = cur;
            if (cur.val > val) {
                cur = cur.left;
            } else {
                cur = cur.right;
            }
        }
        Node node = new Node(val);
        if (parent == null) {
            root = node;
            return true;
        }
        if (parent.val > val) {
            parent.left = node;
        } else {
            parent.right = node;
        }
        return true;
    }

    public boolean remove(int val) {
        Node[] nodes = new Node[2];
        if (!find(val, nodes)) {
            return false;
        }
        Node node = nodes[0];
        Node parent = nodes[1];
        nodes[1] = node;
        findMax(node.left, nodes);
        if (nodes[0] == null) {
            nodes[1] = node;
            findMin(node.right, nodes);
        }
        Node replace = nodes[0];
        Node replace_parent = nodes[1];
        if (replace == null) { // 叶子节点
            if (parent == null) { // 被删除节点是根节点
                root = null;
                return true;
            }
            if (node == parent.left) {
                parent.left = null;
            } else {
                parent.right = null;
            }
            return true;
        }
        if (replace.val > node.val) { // 后继
            if (replace == replace_parent.left) {
                replace_parent.left = replace.right;
            } else {
                replace_parent.right = replace.right;
            }
        } else {
            if (replace == replace_parent.left) {
                replace_parent.left = replace.left;
            } else {
                replace_parent.right = replace.left;
            }
        }
        node.val = replace.val;
        return true;
    }

    private boolean find(int val, Node[] nodes) {
        Node cur = root;
        nodes[1] = null;
        while (cur != null) {
            if (cur.val == val) {
                nodes[0] = cur;
                return true;
            }
            nodes[1] = cur;
            if (cur.val > val) {
                cur = cur.left;
            } else {
                cur = cur.right;
            }
        }
        nodes[0] = null;
        nodes[1] = null;
        return false;
    }

    private void findMax(Node node, Node[] nodes) {
        if (node == null) {
            nodes[0] = null;
            return;
        }
        while (node.right != null) {
            nodes[1] = node;
            node = node.right;
        }
        nodes[0] = node;
    }

    private void findMin(Node node, Node[] nodes) {
        if (node == null) {
            nodes[0] = null;
            return;
        }
        while (node.left != null) {
            nodes[1] = node;
            node = node.left;
        }
        nodes[0] = node;
    }

}
