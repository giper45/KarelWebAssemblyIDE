import React, { useState, useEffect } from "react";

const ScrollToTopButton = () => {
  const [visible, setVisible] = useState(false);
  const [hovered, setHovered] = useState(false);

  useEffect(() => {
    const handleScroll = () => {
      setVisible(window.scrollY > 300);
    };
    window.addEventListener("scroll", handleScroll);
    return () => window.removeEventListener("scroll", handleScroll);
  }, []);

  return (
    <button
      onClick={() => window.scrollTo({ top: 0, behavior: "smooth" })}
      onMouseEnter={() => setHovered(true)}
      onMouseLeave={() => setHovered(false)}
      aria-label="Scroll to top"
      style={{
        position: "fixed",
        bottom: "1.5rem",
        right: "1.5rem",
        zIndex: 50,
        background: hovered ? "#2563eb" : "rgba(37,99,235,0.08)",
        color: hovered ? "#fff" : "rgba(37,99,235,0.35)",
        padding: "0.75rem 1.25rem",
        borderRadius: "9999px",
        boxShadow: hovered ? "0 2px 8px rgba(0,0,0,0.15)" : "none",
        border: "none",
        cursor: "pointer",
        opacity: visible ? (hovered ? 1 : 0.8) : 0,
        pointerEvents: visible ? "auto" : "none",
        transition: "all 0.2s",
        fontSize: "1.25rem",
      }}
    >
      ↑ Top
    </button>
  );
};

export default ScrollToTopButton