import java.util.Arrays;
import java.util.Random;

public class BalancedBinaryTree {
    public static void main(String[] args) {
        if (args.length < 1) {
            return;
        }
        int len = Integer.parseInt(args[0]);
        int[] nums = new int[len];
        Random rand = new Random();
        BalancedBinaryTree tree = new BalancedBinaryTree();
        for (int i = 0; i < len;) {
            int val = rand.nextInt(1000);
            if (tree.insert(val)) {
                nums[i] = val;
                i++;
            }
        }
        System.out.println(Arrays.toString(nums));
        System.out.println("tree height " + Node.getHeight(tree.root));
        BinaryTree.inorderVisit(tree.root);
        for (int i = 0; i < len; i++) {
            tree.remove(nums[i]);
            //System.out.println("tree height " + Node.getHeight(tree.root));
            BinaryTree.inorderVisit(tree.root);
        }
    }

    public Node root = null;
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
        node.parent = parent;
        balance(node);
        return true;
    }
    public boolean remove(int val) {
        Node node = find(val);
        if (node == null) {
            return false;
        }
        Node replace = findMax(node.left);
        if (replace == null) {
            replace = findMin(node.right);
        }
        if (replace == null) {
            if (node.parent == null) {
                root = null;
                return true;
            }
            if (node == node.parent.left) {
                node.parent.left = null;
            } else {
                node.parent.right = null;
            }
            return true;
        }
        if (replace.val > val) { // 后继
            if (replace == replace.parent.left) {
                replace.parent.left = replace.right;
            } else {
                replace.parent.right = replace.right;
            }
            if (replace.right != null) {
                replace.right.parent = replace.parent;
            }
        } else {
            if (replace == replace.parent.left) {
                replace.parent.left = replace.left;
            } else {
                replace.parent.right = replace.left;
            }
            if (replace.left != null) {
                replace.left.parent = replace.parent;
            }
        }
        node.val = replace.val;
        balance(replace);
        return true;
    }
    private void balance(Node node) {
        while (node != null && node.parent != null) {
            node = node.parent;
            int fac = Node.getFactor(node);
            if (Math.abs(fac) <= 1) {
                int childHeight = max(Node.getHeight(node.left),
                        Node.getHeight(node.right));
                if (childHeight + 1 == node.height) {
                    return;
                }
                node.height = childHeight + 1;
                continue;
            }
            if (fac > 0) {
                int facLeft = Node.getFactor(node.left);
                if (facLeft < 0) {
                    leftRotate(node.left);
                }
                rightRotate(node);
            } else {
                int facRight = Node.getFactor(node.right);
                if (facRight > 0) {
                    rightRotate(node.right);
                }
                leftRotate(node);
            }
        }
    }

    private void leftRotate(Node node) {
        if (node == null || node.right == null) {
            return;
        }
        Node parent = node.parent;
        Node right = node.right;
        if (parent == null) {
            root = right;
        } else if (node == parent.left) {
            parent.left = right;
        } else {
            parent.right = right;
        }
        right.parent = parent;

        node.right = right.left;
        if (node.right != null) {
            node.right.parent = node;
        }
        node.height = max(Node.getHeight(node.left),
                Node.getHeight(node.right)) + 1;

        right.left = node;
        node.parent = right;
        right.height = max(Node.getHeight(right.left),
                Node.getHeight(right.right)) + 1;
    }

    private void rightRotate(Node node) {
        if (node == null || node.left == null) {
            return;
        }
        Node parent = node.parent;
        Node left = node.left;
        if (parent == null) {
            root = left;
        } else if (node == parent.left) {
            parent.left = left;
        } else {
            parent.right = left;
        }
        left.parent = parent;

        node.left = left.right;
        if (node.left != null) {
            node.left.parent = node;
        }
        node.height = max(Node.getHeight(node.left), 
                Node.getHeight(node.right)) + 1;

        left.right = node;
        node.parent = left;
        left.height = max(Node.getHeight(left.left),
                Node.getHeight(left.right)) + 1;
    }

    private Node find(int val) {
        Node node = root;
        while (node != null) {
            if (node.val == val) {
                return node;
            }
            node = node.val > val ? node.left : node.right;
        }
        return null;
    }

    private Node findMax(Node node) {
        while (node != null && node.right != null) {
            node = node.right;
        }
        return node;
    }

    private Node findMin(Node node) {
        while (node != null && node.left != null) {
            node = node.left;
        }
        return node;
    }

    private int max(int a, int b) {
        return a > b ? a : b;
    }
}
